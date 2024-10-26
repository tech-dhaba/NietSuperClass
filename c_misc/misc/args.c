//parsing command line arguments in c

#include<stdio.h>
#include<assert.h>

static char *shift(int* argc, char*** argv){
  assert(*argc>0);
  char* result=**argv;
  *argc-=1;
  *argv+=1;
  return result;
}

int main(int argc,char* argv[]){
  printf("%d",argc);  
  while(argc){	
    printf("%s ",shift(&argc,&argv));
  }
  printf("\n");
  return 0;
}
