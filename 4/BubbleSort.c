#include <stdio.h>

int main(void){
    int data_size; scanf("%d",&data_size); 

    int large,num;

    int data[data_size];
    for (int i = 0; i < data_size; i++){
		scanf("%d",&num);
		data[i]=num;
	}
    
    for (int i = 0; i < data_size; i++){
        for (int j = i + 1; j < data_size; j++){
            if (data[i] > data[j]){
                large = data[i];
                data[i] = data[j];
                data[j] = large;
            }
        }
    }

    printf("result:");
    for(int i = 0; i < data_size; i++){
        printf(" %d", data[i]);
    }
    printf("\n");
}
