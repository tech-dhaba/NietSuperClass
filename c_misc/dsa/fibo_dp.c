//program to find nth fibonacci number using dynamic programming

#include<stdio.h>
#include<string.h>
long long dp[100001];

long long fibo_dp(int n){
    if(n==1||n==2){
        dp[n]=1;
        return 1;
    }
    return (dp[n-1]!=-1?dp[n-1]:(dp[n-1]=fibo_dp(n-1)))+(dp[n-2]!=-1?dp[n-2]:(dp[n-2]=fibo_dp(n-2)));  
}

int main(void){
memset(dp,-1,100001);
int n;scanf("%d",&n);
printf("%lld",fibo_dp(n));
return 0;
}