#include <stdio.h>
int doublee(int *x){
    *x=(*x)*2;
    return 2*(*x);
}

int main(){
    int a=10,b=20;
    int*p=&a;
    char*name="namee name";
    printf("%s\n",name);
    // char name[100]="namee";

    printf("The double of  is %d\n",doublee(p));
    printf("%d\n",a);
    return 0;
}