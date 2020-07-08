#include<stdio.h>
int main(){
    long long int first_money=100,year=0,lim;
    scanf("%lld",&lim);
    while(first_money<lim){
        first_money+=first_money/100;
        year++;
    }
    printf("%lld\n",year);
}