#include<stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 4221
#define SO_REUSEPORT 15

#define p(x) printf("%d\n", x)

int main(){
    int serverfiledescriptor, clientfiledescriptor;
    socklen_t clientlength;
    struct sockaddr_in server_address, client_address;
    
    memset(&server_address, 0, sizeof(server_address));
    memset(&client_address, 0, sizeof(client_address));

    char buffer[512];

    serverfiledescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(serverfiledescriptor < 0){
        fprintf(stderr, "Error creating socket\n");
        return 1;
    }

     int reuse = 1;
  if (setsockopt(serverfiledescriptor, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) <
      0) {
    printf("SO_REUSEPORT failed:\n");
    return 1;
  }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = 0;

    if(bind(serverfiledescriptor, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        fprintf(stderr, "Error binding socket\n");
        return 1;
    }

    if(listen(serverfiledescriptor, 5) < 0){
        fprintf(stderr, "Error listening on socket\n");
        return 1;
    }

    clientlength = sizeof(client_address);

    clientfiledescriptor = accept(serverfiledescriptor, (struct sockaddr *)&client_address, &clientlength);
    if(clientfiledescriptor < 0){
        fprintf(stderr, "Error accepting connection\n");
        return 1;
    }

    memset(buffer, 0, 512);
    if(read(clientfiledescriptor, buffer, 511) < 0){
        fprintf(stderr, "Error reading from socket\n");
        return 1;
    }

    printf("Received: %s\n", buffer);

    char *url = strtok(buffer, "/");
    url = strtok(NULL, "/");
    url = strtok(NULL, " ");
    printf("URL: %s\n", url); 

   int len=strlen(url);
   p(len);

    char *message=(char *)malloc(1000*sizeof(char));
    strcat(message,"HTTP/1.1 200 OK\r\n");
    strcat(message,"Content-Type: text/plain\r\n");
    strcat(message,"Content-Length: 12\r\n");
    strcat(message,"\r\n");
    strcat(message,url);



    if(write(clientfiledescriptor, message, strlen(message)) < 0){
        fprintf(stderr, "Error writing to socket\n");
        return 1;
    }

    close(clientfiledescriptor);
    close(serverfiledescriptor);
    free(message);

    return 0;
}