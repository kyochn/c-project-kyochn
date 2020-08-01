#include<stdio.h>

int fib(int);

int fib(int n){
    if(n==0||n==1) return n;

    int m=fib(n-1)+fib(n-2);
    return m;
}

int main(){
    int n,ans;
    scanf("%d",&n);

    ans=fib(n);
    printf("%d\n",ans);
}