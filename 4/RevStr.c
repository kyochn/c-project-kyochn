#include <stdio.h>
#include <string.h>
 
 
void revStr(char *str){
	int size = strlen(str);
	int i,j;
	char tmp;
	
	for(i = 0, j = size - 1; i < size / 2; i++, j--){
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
	}
}
 
int main(){
	char str[256];
	scanf("%s", &*str);
	revStr(str);	
	printf("%s\n", str);
}