#include<stdio.h>

inline int add(int a, int b){
  return a+b;
}

int main(void){
  int (*sum)(int,int)=&add;
  printf("%d",sum(2,5));
}
