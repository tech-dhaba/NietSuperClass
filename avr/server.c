#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

#define BUFFER_SIZE 256

int uart_fd = -1;
int server_fd = -1;
int client_fd = -1;

void cleanup() {
    if (uart_fd >= 0) close(uart_fd);
    if (client_fd >= 0) close(client_fd);
    if (server_fd >= 0) close(server_fd);
}

void handle_signal(int signal) {
    printf("Received signal %d, cleaning up and exiting...\n", signal);
    cleanup();
    exit(0);
}

int setup_uart(const char *uart_device) {
    int fd = open(uart_device, O_RDONLY | O_NOCTTY | O_NONBLOCK);
    if (fd < 0) {
        perror("Error opening UART device");
        return -1;
    }
    return fd;
}

int setup_server(const char *ip, int port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("Error creating socket");
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        perror("Invalid IP address");
        close(fd);
        return -1;
    }

    int reuse = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("SO_REUSEADDR failed");
        close(fd);
        return -1;
    }

    if (bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        close(fd);
        return -1;
    }

    if (listen(fd, 5) < 0) {
        perror("Error listening on socket");
        close(fd);
        return -1;
    }

    return fd;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <IP> <Port> <UART Device>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    const char *uart_device = argv[3];

    // Register signal handler for cleanup
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);

    uart_fd = setup_uart(uart_device);
    if (uart_fd < 0) return 1;

    server_fd = setup_server(ip, port);
    if (server_fd < 0) {
        cleanup();
        return 1;
    }

    printf("Server listening on %s:%d\n", ip, port);

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    while (1) {
        // Accept client connection
        client_fd = accept(server_fd, NULL, NULL);
        if (client_fd < 0) {
            perror("Error accepting client connection");
            continue;
        }

        printf("Client connected\n");

        while (1) {
            // Read data from UART
            memset(buffer, 0, sizeof(buffer));
            bytes_read = read(uart_fd, buffer, sizeof(buffer) - 1);
            if (bytes_read < 0) {
                if (errno != EAGAIN) {
                    perror("Error reading from UART");
                }
                usleep(100000); // Wait 100ms before retrying
                continue;
            }

            if (bytes_read == 0) {
                continue; // No data available, retry
            }

            // Send data to client
            if (write(client_fd, buffer, bytes_read) < 0) {
                perror("Error writing to client");
                break;
            }

            // Print debug information
            printf("Sent to client: %s\n", buffer);
        }

        close(client_fd);
        client_fd = -1;
    }

    cleanup();
    return 0;
}

