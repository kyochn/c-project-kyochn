#include<stdio.h>
#include<stdlib.h>

int compare_int(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}

int main(){
	int count,num;
	scanf("%d",&count);
  
	int data[count];
	for (int i = 0; i < count; i++){
		scanf("%d",&num);
		data[i]=num;
	}

    qsort(data, count, sizeof(int), compare_int);

	printf("result:");
    for (int i = 0; i < count; i++) {
		printf(" ");
        printf("%d", data[i]);
    }
    printf("\n");
}
