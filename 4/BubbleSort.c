#include <stdio.h>

int main(void){
    int count; scanf("%d",&count); 

    int large,num;

    int data[count];
    for (int i = 0; i < count; i++){
		scanf("%d",&num);
		data[i]=num;
	}
    
    for (int i = 0; i < count; i++){
        for (int j = i + 1; j < count; j++){
            if (data[i] > data[j]){
                large = data[i];
                data[i] = data[j];
                data[j] = large;
            }
        }
    }

    printf("result:");
    for(int i = 0; i < count; i++){
        printf(" %d", data[i]);
    }
    printf("\n");
}
