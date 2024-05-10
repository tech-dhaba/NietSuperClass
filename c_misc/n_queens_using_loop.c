#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int queens[20];

int check(const int row,const int col){
    for(int i=0;i<row;i++){
       int prow=i;
        int pcol=queens[i];
        if(col==pcol || abs(pcol-col)==abs(prow-row))return 0;
    }
    return 1;
}

int rec(int row,int n){
    if(row==n)return 1;
    int ans=0;
    for(int col=0;col<n;col++){
        if(check(row,col)){
            queens[row]=col;
            ans+=rec(row+1,n);
            queens[row]=-1;
        }
    }
    return ans;
}

int loop(int n){
    int ans=0;
    for(int row=0;row<n;row++){
        for(int col=0;col<n;col++){
            if(check(row,col)){
                if(row==n-1){
                    ans++;
                     row--;
                    col=queens[row];
                    int temp= queens[row];
                        queens[row]=-1;
                    if(temp==n-1){
                        row--;
                        col=queens[row];
                        queens[row]=-1;
                    }
                    continue;
                }
                queens[row]=col;
                break;
            }
            else{
                if(col==n-1){
                    row--;
                    col=queens[row];
                    int temp=queens[row];
                    queens[row]=-1;
                    if(temp==n-1 && (--row)>=0){
                        col=queens[row];
                        queens[row]=-1;
                    }
                    else{
                        if(temp==n-1 && row<=0)return ans;
                    }
                }    
            }
        }
    }
    return ans;
}

int main(void){
    memset(queens,-1,20);
    int n;scanf("%d",&n);
    printf("%d ",rec(0,n));
    printf("%d",loop(n));
}