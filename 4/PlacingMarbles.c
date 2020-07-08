#include<stdio.h>
int main(){
    int count=0;
    
    char str[3];
    scanf("%s",&*str);
    
    if(str[0]=='1') count++;
    if(str[1]=='1') count++;
    if(str[2]=='1') count++;

    printf("%d\n",count);
}