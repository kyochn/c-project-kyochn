#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *file[2];
    char str[256];

    printf("%d\n", argc);

    if (argc < 2) {
        printf("failed to open\n");
        return 1;
    }

    /*  file[0] = fopen(argv[1], "r");
      file[1] = fopen(argv[2], "r"); */

    for (int i = 0; i < argc - 1; i++) {
        file[i] = fopen(argv[i + 1], "r");
        if(file[i]==NULL){
          printf("failed to open\n\n");
          continue;
        }
        while ((fgets(str, 256, file[i])) != NULL) {
            printf("%s", str);
        }
        printf("\n\n");
        fclose(file[i]);
    }
    return 0;
}
