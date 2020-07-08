#include<stdio.h>
int main(){
    int N; scanf("%d",&N);
    int num[N];
    int result=10000,count=0;
    for (int i = 0; i < N; i++){
        count=0;
        scanf("%d",&num[i]);
        while (num[i]%2==0){
            count++;
            num[i]/=2;
        }
        if(result>count) result=count;
    }
    printf("%d\n",result);
}