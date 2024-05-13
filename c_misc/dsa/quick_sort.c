//program to implement quick sort

#include <stdio.h>

void swap(int* a, int* b) {
    if(a==b)return;
    *a^=*b;
    *b^=*a;
    *a^=*b;
    return;
}

void quicjksort(int *arr,int left,int right){
    if(left>=right)return;
    int pivot=right-1;
    int i=left-1,j=left;
    for(; j<right;j++){
        if(arr[j]<arr[pivot]){
            i++;
            swap(arr+i,arr+j);
        }
    }
    i++;
    swap(arr+pivot,arr+i);
    quicjksort(arr,left,i-1);
    quicjksort(arr,i+1,right);
    return;
}

int main(void){
    int arr[]={1,5,7,2,4,8,1,3,6,9,0,2,4,6,8,3,5,7,9,0};
    quicjksort(arr,0,20);
    for(int i=0;i<20;i++)printf("%d ",arr[i]);
}