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

//typedef enum {red,orange,yellow,blue,sky,green,brown,gray} Color;

/*typedef struct{
    Triple triple;
    Color color;
}Triangle; */

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

/*Triangle generate(){
    static int color;
    Triple triple=make_triangle();
    Triangle triangle={triple,(Color)color};
    color++;
    if(color>7) color=0;
    return triangle;
} */

void centering_triangle(Triple *triple){
    double gx=(triple->A.x+triple->B.x+triple->C.x)/3;
    double gy=(triple->A.y+triple->B.y+triple->C.y)/3;
    triple->A.x-=gx; triple->A.y-=gy;
    triple->B.x-=gx; triple->B.y-=gy;
    triple->C.x-=gx; triple->C.y-=gy;
}

int main() {
    srand((unsigned int)time(NULL));
    Triple triple = make_triangle();
    printf("前のAの座標：(%lf,%lf)\n", triple.A.x, triple.A.y);
    printf("前のBの座標：(%lf,%lf)\n", triple.B.x, triple.B.y);
    printf("前のCの座標：(%lf,%lf)\n", triple.C.x, triple.C.y);
    printf("面積：%lf\n", triple.area);
    printf("\n");
    centering_triangle(&triple);
    printf("今のAの座標：(%lf,%lf)\n", triple.A.x, triple.A.y);
    printf("今のBの座標：(%lf,%lf)\n", triple.B.x, triple.B.y);
    printf("今のCの座標：(%lf,%lf)\n", triple.C.x, triple.C.y);
    printf("面積：%lf\n", triple.area);
}