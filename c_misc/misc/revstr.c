//this program reverses a string

#include<stdio.h>
#include<string.h>

char *revstr(const int len, char str[]){
  int i=0;
  while(i<len/2){
    str[i]^=str[len-i-1];
    str[len-i-1]^=str[i];
    str[i]^=str[len-i-1];
    i++;
  }
  return str;
}

int main(void){
  char str[10];
  scanf("%s",str);
  printf("%s\n",revstr(strlen(str),str));
  return 0;
}

