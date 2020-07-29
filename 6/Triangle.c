#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

typedef struct{
    double x;
    double y;
} Point;

typedef struct{
    Point A;
    Point B;
    Point C;
    double area;
} Triple;

typedef enum {red,orange,yellow,blue,sky,green,brown,gray} Color;

typedef struct{
    Triple triple;
    Color color;
}Triangle;

bool crash(Triple triple){
    if(triple.A.x==triple.B.x){
        if(triple.A.y==triple.B.y) return true;
    }else if(triple.A.x==triple.C.x){
        if(triple.A.y==triple.C.y) return true;
    }else if(triple.B.x==triple.C.x){
        if(triple.B.y==triple.C.y) return true;
    }else{
        return false;
    }
}

bool is_triangle(Triple triple){
    double tilt1,tilt2;

    if(crash(triple)){
        return false;
    }else{
        tilt1=(triple.A.y-triple.B.y)/(triple.A.x-triple.B.x);
        tilt2=(triple.A.y-triple.C.y)/(triple.A.x-triple.C.x);
        if(tilt1==tilt2) return false;
        else return true;
    }
}

Triple make_triangle(){
    Triple triple;
    begin:
    triple.A.x=rand()%50;
    triple.A.y=rand()%50;
    triple.B.x=rand()%50;
    triple.B.y=rand()%50;
    triple.C.x=rand()%50;
    triple.C.y=rand()%50;

    if(!is_triangle(triple)) goto begin;

    double distance1,distance2,distance3,heron;
    distance1=sqrt((triple.A.x-triple.B.x)*(triple.A.x-triple.B.x)+(triple.A.y-triple.B.y)*(triple.A.y-triple.B.y));
    distance2=sqrt((triple.B.x-triple.C.x)*(triple.B.x-triple.C.x)+(triple.B.y-triple.C.y)*(triple.B.y-triple.C.y));
    distance3=sqrt((triple.A.x-triple.C.x)*(triple.A.x-triple.C.x)+(triple.A.y-triple.C.y)*(triple.A.y-triple.C.y));
    heron=(distance1+distance2+distance3)/2;
    triple.area=sqrt(heron*(heron-distance1)*(heron-distance2)*(heron-distance3)); 

    if(triple.area>100){
       goto begin;
    }else{
        return triple;
    }
}

Triangle generate(){
    static int color;
    Triple triple=make_triangle();
    Triangle triangle={triple,(Color)color};
    color++;
    if(color>7) color=0;
    return triangle;
}

int main(){
    int i;
    srand((unsigned int) time(NULL));
    for(i=0;i<10;i++){
        Triangle triangle=generate();
        printf("Aの座標：(%lf,%lf)\n",triangle.triple.A.x,triangle.triple.A.y);
        printf("Bの座標：(%lf,%lf)\n",triangle.triple.B.x,triangle.triple.B.y);
        printf("Cの座標：(%lf,%lf)\n",triangle.triple.C.x,triangle.triple.C.y);
        printf("面積：%lf\n",triangle.triple.area);
        switch(triangle.color){
            case 0:
                printf("色：赤\n");
                break;
            case 1:
                printf("色：橙\n");
                break;
            case 2:
                printf("色：黄\n");
                break;
            case 3:
                printf("色：青\n");
                break;
            case 4:
                printf("色：水\n");
                break;
            case 5:
                printf("色：緑\n");
                break;
            case 6:
                printf("色：茶\n");
                break;
            case 7:
                printf("色：灰\n");
                break;
        }
        if(i!=9) printf("\n");
    }
}