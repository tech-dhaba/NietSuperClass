#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define port 4221
#define SO_REUSEPORT 15

int server_init(int port_no);
int client_init(int serverfiledescriptor);
void client_handler(int serverfiledescriptor, int clientfiledescriptor);//{return;};

int main(int argc, char *argv[]){

    int serverfiledescriptor, clientfiledescriptor;
   

    serverfiledescriptor =  server_init(port);
    if(serverfiledescriptor < 0){
        fprintf(stderr, "Error creating socket\n");
        return 1;
    }    

    printf("Server listening on port %d\n", port);

    
    
        clientfiledescriptor = client_init(serverfiledescriptor);
        if(clientfiledescriptor < 0){
            fprintf(stderr, "Error accepting connection\n");
        }

        printf("Client connected\n");

        
        client_handler(serverfiledescriptor, clientfiledescriptor);

        

    
    return -1;
}

int server_init(int port_no){
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
    buffer[bytes_read] = '\0';
    printf("Received: %s\n", buffer);
        char *temp=strcpy(buffer,buffer);
        char *temp1=strtok(temp,"\r\n");
        printf("%s\n", temp1);
    while(1){
        char *temp3 =strtok(temp1,":");
        printf("%s\n", temp3);
        if((strncmp(temp3,"User-Agent",10)==0)){
        sprintf(response,
                "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: "
                "%ld\r\n\r\n"
                "%s\r\n\r\n",
                strlen(temp3), temp3);
        write(clientfiledescriptor, response, strlen(response));
        close(clientfiledescriptor);
        return;
        }
        temp1=temp;
        temp=strtok(NULL,"\r\n");
        // temp2=strtok(NULL,":");
    char* response1="HTTP/1.1 404 Not Found\r\n\r\n";
write(clientfiledescriptor,response1,strlen(response1));
close(clientfiledescriptor);
    return;       
}
}