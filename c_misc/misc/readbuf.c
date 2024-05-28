#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int fd = open("./name", O_RDONLY);
    if(fd == -1){
        perror("open");
        return 1;
    }
    char buf[1024];
    memset(buf,0,1024);
    read(fd,buf,sizeof(buf));
    char* tempp[1024] = {0};
    for(int i=0;i<1024;i++){
        tempp[i] = (char*)malloc(100);
    }
    char temppp[1024];
    // char* ptr=temppp;
    int i=0;
    // write(1,buf,1024);
    char* temp=strtok(buf," ");
    char prev[100];
    do{
        strncpy(prev,temp,100);
        // printf("\n%s",prev);
        tempp[i++] = temp;
        if(temp==NULL){
            break;
        }
        strcat(temppp,temp);
        strcat(temppp," ");
    }while(temp=strtok(NULL," "));
    for(int j=i-1;j>=0;j--){
        printf("%s ",tempp[j]);
    }
    strtok(prev,"!");
    printf("%s",temppp);
    // printf("%s",prev);
    close(fd);
}