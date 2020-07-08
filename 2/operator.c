#include<stdio.h>

int main(){
    int x=5,y=3;
    //算術演算子
    printf("%d\n",x+y);
    printf("%d\n",x-y);
    printf("%d\n",x*y);
    printf("%d\n",x/y);
    printf("%d\n",x%y);

    printf("\n");


    //比較演算子(真なら1,偽なら0が出力される)
    printf("%d\n",x==y);
    printf("%d\n",x!=y);
    printf("%d\n",x<y);
    printf("%d\n",x<=y);
    printf("%d\n",x>y);
    printf("%d\n",x>=y);

    printf("\n");

    
    //論理演算子(真なら1,偽なら0が出力される)
    printf("%d\n",x>1&&y>1); //真
    printf("%d\n",x>1||y<1); //真
    printf("%d\n",!x); //偽

    printf("\n");

    //複合代入演算子、初めx=5
    //インクリメント,デクリメントは前置後置で挙動が変わる
    printf("%d\n",x+=5); //x=10
    printf("%d\n",x++); //加算が%dにxを渡した後に行われるので10と表示されるが最終x=11となる(要は表示してから計算が行われる)
    printf("%d\n",++x); //加算した後に%dに渡されるので12と表示される
    printf("%d\n",x-=5); //x=7
    printf("%d\n",x--); //減算が%dにxを渡した後に行われるので7と表示されるが最終x=6となる
    printf("%d\n",--x); //減算した後に%dに渡されるので5と表示される
    printf("%d\n",x*=5); //x=25
    printf("%d\n",x/=5); //x=5
    printf("%d\n",x%=3); //x=2
}