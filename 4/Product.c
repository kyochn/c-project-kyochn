#include<stdio.h>
int main(){
    int a,b;
    scanf("%d %d",&a,&b);
    if((a*b)%2==0) printf("Even\n");
    else printf("Odd\n");
}