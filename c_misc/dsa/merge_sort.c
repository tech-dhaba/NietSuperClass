//program to implement merge sort

#include<stdio.h>
#include<stdlib.h>

int x=0;
void merge(int arr[],int lb,int mid,int ub){
  x++;
  int i=0;
  int j=0;
  int k=lb;
  int* L=(int*)malloc((mid-lb+1)*sizeof(int));
  int* R=(int*)malloc((ub-mid)*sizeof(int));
  for(int i=0;i<mid+1-lb;i++){
    L[i]=arr[i+lb];
  }
  for(int i=0;i<ub-mid;i++){
    R[i]=arr[i+mid+1];
  }
  while(i<mid+1-lb && j<ub-mid){
     if(L[i]<=R[j]){
       arr[k]=L[i];
       i++;
     }else{
       arr[k]=R[j];
       j++;
     }
     k++;
  }
  while(i<mid+1-lb){
    arr[k]=L[i];
    k++;
    i++;
  }
  while(j<ub-mid){
    arr[k]=R[j];
    k++;
    j++;
  }
  free(L);
  free(R);
}
      

void mergesort(int arr[],int lb,int ub){
  x++;
  int mid=lb+(ub-lb)/2;
  if(lb<ub){
    mergesort(arr,lb,mid);//(0,11),(0,5),(0,2),(0,1),(0,0)
    mergesort(arr,mid+1,ub);
    merge(arr,lb,mid,ub);
  }
}

int main(){
  int arr[]={4,5,3,1,7,98,43,12,56,76,43,78,100,1,2,3,4,5,6,7,8,9,11,22,33,44,55,33,32,21,1};
  int lb=0;
  int ub=sizeof(arr)/sizeof(int)-1;
  mergesort(arr,lb,ub);
  for(int i=0;i<sizeof(arr)/sizeof(int);i++)printf("%d ",arr[i]);
  printf("\n%d\n",x);
}
    
