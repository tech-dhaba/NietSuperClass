//program to ping an address using sockets

#include<stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

// #define IP "142.250.206.142" //google.com
//#define IP "172.25.231.135"//yahoo.com
#define IP "192.168.1.39"
// #define IP "127.0.0.1"
#define PORT 8080
// #define PORT 4221

int main(){
    int socketfiledescriptor;
    struct sockaddr_in server_address;
    char buffer[512];
    char *message = "HEAD / HTTP/1.0\r\n\r\n";

    socketfiledescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfiledescriptor < 0){
        fprintf(stderr, "Error creating socket\n");
        return 1;
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(IP);

    if(connect(socketfiledescriptor, (struct sockaddr *)&server_address, sizeof(server_address)) < 0){
        fprintf(stderr, "Error connecting to server\n");
        return 1;
    }

    if(send(socketfiledescriptor, message, strlen(message), 0) < 0){
        fprintf(stderr, "Error sending message\n");
        return 1;
    }

    while(recv(socketfiledescriptor, buffer, 1024, 0) > 0){
        printf("%s", buffer);
    }
    // write(socketfiledescriptor, buffer, 1024);
    // memset(buffer, 0, 1024);
    // while(read(socketfiledescriptor, buffer, 1024)>0)
    // printf("\n%s\n", buffer);

    close(socketfiledescriptor);

    return 0;
} 
