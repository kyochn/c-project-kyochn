#include <stdio.h>
#define MAX 1000000

int main(){
  int p[MAX];
  int num=1;

  int demand; scanf("%d",&demand);

  for(int i=1 ; i<MAX ; i++) p[i] = 0;

  for(int i=2 ; i<=MAX/2 ; i++){
    for(int j=2 ; i*j<=MAX ; j++){
      if(p[i*j-1] == 0)
        p[i*j-1] = 1;
    }
  }
  for(int i=1 ; i<MAX ; i++){
    if(p[i] == 0){
        if(num==demand){
            printf("%d\n",i+1);
            break;
        }
        num++;
    }
  }
}