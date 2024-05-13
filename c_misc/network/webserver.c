#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define SO_REUSEPORT 15

int server_init(int port);
int client_init(int serverfiledescriptor);
void client_handler(int serverfiledescriptor, int clientfiledescriptor);//{return;};

int main(int argc, char *argv[]){

    int serverfiledescriptor, clientfiledescriptor;
    char *port;
    if(argc < 2){
       fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    }else{
        port = argv[1];
    }

    serverfiledescriptor =  server_init(atoi(port));
    if(serverfiledescriptor < 0){
        fprintf(stderr, "Error creating socket\n");
        return 1;
    }    

    printf("Server listening on port %s\n", port);

    
    while(1){
        clientfiledescriptor = client_init(serverfiledescriptor);
        if(clientfiledescriptor < 0){
            fprintf(stderr, "Error accepting connection\n");
            continue;
        }

        printf("Client connected\n");

        if(fork() == 0){
            client_handler(serverfiledescriptor, clientfiledescriptor);

        }

    }
    return -1;
}

int server_init(int port){
    int serverfiledescriptor;

    struct sockaddr_in server_address;

    memset(&server_address, 0, sizeof(server_address));

    serverfiledescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if(serverfiledescriptor < 0){
        return -1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = 0;

      int reuse = 1;
  if (setsockopt(serverfiledescriptor, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) <
      0) {
    printf("SO_REUSEPORT failed: %s \n", strerror(errno));
    return 1;
  }
    if(bind(serverfiledescriptor, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        fprintf(stderr, "Error binding socket\n");
        return -1;
    }

    if(listen(serverfiledescriptor, 5) < 0){
        fprintf(stderr, "Error listening on socket\n");
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
        fprintf(stderr, "Error accepting connection\n");
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
        fprintf(stderr, "Error reading from client\n");
        return;
    }
    write(1, buffer, bytes_read);
    char* method = strtok(buffer, " ");
    char* path = strtok(NULL, " ");
    char* protocol = strtok(NULL, "\r\n");
    char *version = strtok(protocol, "/");
    version = strtok(NULL, "\r\n");
    // printf("Method: %s\n", method);
    // printf("Path: %s\n", path);
    // printf("Protocol: %s\n", protocol);
    // printf("Version: %s\n", version);
    
    if (strcmp(path, "/") == 0) 
    strcpy(response, "HTTP/1.1 200 OK\r\n\r\n");

    
    else if (strncmp(path, "/echo/", 6) == 0) {
        strtok(path, "/");
        char *input = &path[6];
        printf("%s\n", input);
        sprintf(response,
                "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: "
                "%ld\r\n\r\n"
                "%s\r\n\r\n",
                strlen(input), input);
    }

    
    else strcpy(response, "HTTP/1.1 404 Not Found\r\n\r\n");

    write(clientfiledescriptor, response, strlen(response));
    close(clientfiledescriptor);

    return;
}
