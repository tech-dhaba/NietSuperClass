//etracts filename without extension from a given filename

#include<stdio.h>
#include<string.h>

char* revstr(const int len, char str[]){
  int i=0;
  while(i<len/2){
    str[i]^=str[len-i-1];
    str[len-i-1]^=str[i];
    str[i]^=str[len-i-1];
    i++;
  }
  return str;
}

char *name(char arr[]){
  revstr(strlen(arr),arr);
  char *result=strtok(arr,".");
  result=strtok(NULL,"\0");
  return revstr(strlen(result?result:arr),result?result:arr);
}

int main(){
  char arr[10];
  scanf("%s",arr);
  char *result=name(arr);
  printf("%s\n",result); 
  return 0;
}
