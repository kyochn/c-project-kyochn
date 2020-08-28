// export PATH=$PATH:$(pwd)
#include <signal.h>
#include <stdio.h>
#include <string.h>

volatile sig_atomic_t flag = 0;
void handler(int sig) { flag = 1; }

int main(int argc, char *argv[]) {
    FILE *file[argc - 1];
    char str[256];
    char c;

//    printf("%d\n", argc);
//    printf("%s\n",argv[1]);

    signal(SIGQUIT, handler);

    if (argc < 2) {
        while (!flag) {
            std:
            c = getchar();
            printf("%c", c);
        }
    }

    if (!strcmp(argv[1],"-")) {
        goto std;
    } 

    for (int i = 0; i < argc - 1; i++) {
        file[i] = fopen(argv[i + 1], "r");
        if (file[i] == NULL) {
            printf("no exist\n\n");
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
