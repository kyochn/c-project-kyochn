#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main(){
    srand((unsigned int) time(NULL));
    int result=rand()%6;
    if(result<3){
        printf("吉です\n");
    }else if(result<5){
        printf("凶です\n");
    }else{
        printf("大吉です\n");
    }
}