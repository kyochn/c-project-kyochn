#include<stdio.h>
#include<math.h>

float my_hypot(float,float);

float my_hypot(float x, float y){
    float X=x*x;
    float Y=y*y;
    return sqrtf(X+Y);
} 

int main(){
    float x,y;
    scanf("%f %f",&x,&y);

    float distance=my_hypot(x,y);

    printf("%f\n",distance);
}