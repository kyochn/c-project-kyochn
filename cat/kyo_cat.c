// export PATH=$PATH:$(pwd)
#include <signal.h>
#include <stdio.h>
#include <string.h>

volatile sig_atomic_t flag = 0;
void handler(int sig) { flag = 1; }

int main(int argc, char *argv[]) {
    FILE *file[argc - 1];
    char str[256], c;
    int line_number = 1;
    
    signal(SIGINT, handler);

    if (argc < 2 || !strcmp(argv[1], "-")) {
        while (!flag) {
            c = getchar();
            printf("%c", c);
        }
    }

    if (!strcmp(argv[1], "-help")) {
        file[1] = fopen("help.md", "r");
        while ((fgets(str, 256, file[1])) != NULL) {
            printf("%s", str);
        }
        printf("\n\n");
        fclose(file[1]);
        goto end;
    }

    if (!strcmp(argv[1], "-w")) {
        for (int i = 1; i < argc - 1; i++) {
            file[i] = fopen(argv[i + 1], "w");
            while ((fgets(str, 256, file[i])) != NULL) {
                printf("%s", str);
            }
            printf("\n\n");
            fclose(file[i]);
        }
        goto end;
    }

    if (!strcmp(argv[1], "-a")) {
        for (int i = 1; i < argc - 1; i++) {
            file[i] = fopen(argv[i + 1], "a");
            while ((fgets(str, 256, file[i])) != NULL) {
                printf("%s", str);
            }
            printf("\n\n");
            fclose(file[i]);
        }
        goto end;
    }

    if (!strcmp(argv[1], "-r+")) {
        for (int i = 1; i < argc - 1; i++) {
            file[i] = fopen(argv[i + 1], "r+");
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
        goto end;
    }

    if (!strcmp(argv[1], "-w+")) {
        for (int i = 1; i < argc - 1; i++) {
            file[i] = fopen(argv[i + 1], "w+");
            while ((fgets(str, 256, file[i])) != NULL) {
                printf("%s", str);
            }
            printf("\n\n");
            fclose(file[i]);
        }
        goto end;
    }

    if (!strcmp(argv[1], "-a+")) {
        for (int i = 1; i < argc - 1; i++) {
            file[i] = fopen(argv[i + 1], "a+");
            while ((fgets(str, 256, file[i])) != NULL) {
                printf("%s", str);
            }
            printf("\n\n");
            fclose(file[i]);
        }
        goto end;
    }

    if (!strcmp(argv[1], "-n")) {
        for (int i = 1; i < argc - 1; i++) {
            file[i] = fopen(argv[i + 1], "r");
            if (file[i] == NULL) {
                printf("no exist\n\n");
                continue;
            }
            while ((fgets(str, 256, file[i])) != NULL) {
                printf("%d %s", line_number, str);
                line_number++;
            }
            printf("\n\n");
            fclose(file[i]);
        }
        goto end;
    }

    if (!strcmp(argv[1], "-e")) {
        for (int i = 1; i < argc - 1; i++) {
            file[i] = fopen(argv[i + 1], "r");
            if (file[i] == NULL) {
                printf("no exist\n\n");
                continue;
            }
            while ((fgets(str, 256, file[i])) != NULL) {
                for(int j=0;j<sizeof(str);j++){
                    if(str[j]=='\n'){
                        str[j]='$';
                        break;
                    }
                } 
                printf("%s\n", str);
            }
            printf("\n");
            fclose(file[i]);
        }
        goto end;
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

end:
    return 0;
}
