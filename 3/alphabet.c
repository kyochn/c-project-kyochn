#include<stdio.h>
#include<ctype.h>

int main(){
    int str;
    str=getchar();

    if(islower(str)) printf("a\n");
    else printf("A\n");
}