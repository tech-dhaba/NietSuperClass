#include<stdio.h>

void swap(int *a,int *b){
    *a=(*a)^(*b);*b=(*a)^(*b);*a=(*a)^(*b);
}

int main(){
    int x=4,y=22;
    void (*swapp)(int *,int*)=swap;
    swapp(&x,&y);
    printf("%d\n%d",x,y);

}