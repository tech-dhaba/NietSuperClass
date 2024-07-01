#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define SO_REUSEPORT 15

int server_init(const char *ip, int port);
int client_init(int serverfiledescriptor);
void client_handler(int serverfiledescriptor, int clientfiledescriptor);

int main(int argc, char *argv[]){
    int serverfiledescriptor, clientfiledescriptor;
    char *ip;
    char *port;

    if(argc < 3){
        fprintf(stderr, "Usage: %s <IP> <port>\n", argv[0]);
        return 1;
    } else {
        ip = argv[1];
        port = argv[2];
    }

    serverfiledescriptor = server_init(ip, atoi(port));
    if(serverfiledescriptor < 0){
        fprintf(stderr, "Error creating socket\n");
        return 1;
    }    

    printf("Server listening on IP %s, port %s\n", ip, port);

    while(1){
        clientfiledescriptor = client_init(serverfiledescriptor);
        if(clientfiledescriptor < 0){
            fprintf(stderr, "Error accepting connection\n");
            continue;
        }

        printf("Client connected\n");

        if(fork() == 0){
            client_handler(serverfiledescriptor, clientfiledescriptor);
            close(clientfiledescriptor);
            exit(0);
        }

        close(clientfiledescriptor);
    }

    close(serverfiledescriptor);
    return 0;
}

int server_init(const char *ip, int port){
    int serverfiledescriptor;
    struct sockaddr_in server_address;
    int reuse = 1;

    memset(&server_address, 0, sizeof(server_address));

    serverfiledescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(serverfiledescriptor < 0){
        perror("Socket creation failed");
        return -1;
    }

    if(setsockopt(serverfiledescriptor, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0){
        perror("SO_REUSEPORT failed");
        close(serverfiledescriptor);
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if(inet_pton(AF_INET, ip, &server_address.sin_addr) <= 0){
        fprintf(stderr, "Invalid IP address\n");
        close(serverfiledescriptor);
        return -1;
    }

    if(bind(serverfiledescriptor, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        perror("Binding failed");
        close(serverfiledescriptor);
        return -1;
    }

    if(listen(serverfiledescriptor, 5) < 0){
        perror("Listening failed");
        close(serverfiledescriptor);
        return -1;
    }

    return serverfiledescriptor;
}

int client_init(int serverfiledescriptor){
    int clientfiledescriptor;
    socklen_t clientlength;
    struct sockaddr_in client_address;

    memset(&client_address, 0, sizeof(client_address));
    clientlength = sizeof(client_address);

    clientfiledescriptor = accept(serverfiledescriptor, (struct sockaddr *)&client_address, &clientlength);
    if(clientfiledescriptor < 0){
        perror("Accepting connection failed");
        return -1;
    }

    return clientfiledescriptor;
}

void client_handler(int serverfiledescriptor, int clientfiledescriptor){
    char buffer[1024];
    int bytes_read;
    char response[1024];

    bytes_read = read(clientfiledescriptor, buffer, sizeof(buffer));
    if(bytes_read < 0){
        perror("Reading from client failed");
        return;
    }

    write(1, buffer, bytes_read);
    char* method = strtok(buffer, " ");
    char* path = strtok(NULL, " ");
    char* protocol = strtok(NULL, "\r\n");
    char *version = strtok(protocol, "/");
    version = strtok(NULL, "\r\n");

    if (strcmp(path, "/") == 0) {
        strcpy(response, "HTTP/1.1 200 OK\r\n\r\n");
    } else if (strncmp(path, "/echo/", 6) == 0) {
        strtok(path, "/");
        char *input = &path[6];
        printf("%s\n", input);
        sprintf(response,
                "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: "
                "%ld\r\n\r\n"
                "%s\r\n\r\n",
                strlen(input), input);
    } else {
        strcpy(response, "HTTP/1.1 404 Not Found\r\n\r\n");
    }

    write(clientfiledescriptor, response, strlen(response));
    return;
}

