#include<stdio.h>
#include<string.h>
int main(){
    char str[256];
    scanf("%s",&*str);

    int size = strlen(str);

    for(int i=0;i<size;i++){
        if(str[i]=='a') str[i]='*';
    }

    printf("%s\n",str);
}