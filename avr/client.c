#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <termios.h>

#define BUFFER_SIZE 256
#define SKIP_COUNT 5 // Number of initial messages to skip
#define UART_DEVICE "/dev/serial0" // Change to appropriate UART device

int open_uart(const char *device) {
    int uart_fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart_fd == -1) {
        perror("Error opening UART");
        return -1;
    }

    struct termios options;
    tcgetattr(uart_fd, &options);

    // Set baud rate
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

    // 8N1 mode
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // Set the new attributes
    tcsetattr(uart_fd, TCSANOW, &options);

    return uart_fd;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP> <Port>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    // Open UART
    int uart_fd = open_uart(UART_DEVICE);
    if (uart_fd < 0) {
        return 1;
    }

    // Create client socket
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        perror("Error creating socket");
        close(uart_fd);
        return 1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid IP address");
        close(client_fd);
        close(uart_fd);
        return 1;
    }

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        close(client_fd);
        close(uart_fd);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    int skip_count = 0;

    while (1) {
        // Receive data from server
        memset(buffer, 0, sizeof(buffer));
        bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes_read < 0) {
            perror("Error reading from server");
            break;
        }

        if (bytes_read > 0) {
            // Skip initial messages
            if (skip_count < SKIP_COUNT) {
                skip_count++;
                continue;
            }

            // Print received data
            printf("Received from server: %s\n", buffer);

            // Transmit data to UART
            ssize_t bytes_written = write(uart_fd, buffer, bytes_read);
            if (bytes_written < 0) {
                perror("Error writing to UART");
                break;
            }
        }

        usleep(1000000); // Wait for 1 second before next read
    }

    close(client_fd);
    close(uart_fd);
    return 0;
}

