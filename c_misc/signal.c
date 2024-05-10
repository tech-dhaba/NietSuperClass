#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
void handle(){
 write(1,"not gonna die tonight",21);
}
int main(){
  signal(SIGINT,handle);
  while(1){
  printf("-_- %d\n",getpid());
  sleep(1);
  }
}
