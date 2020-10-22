#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    while (1) {
        char *tp;
        char str[256];
        fgets(str,sizeof(str),stdin);
        char* cmd[3];

        tp=strtok(str," \n");
        cmd[0]=str;
        while(tp!=NULL){
            tp=strtok(NULL," \n");
            if(tp!=NULL) cmd[1]=tp;
        }
        cmd[2]=NULL;

        int pid = fork();

        if (pid == 0) {
            puts("I am child proc");
            execv(cmd[0], cmd);
            exit(0);
        }

        int status;
        wait(&status);
        printf("Child process exited with status %d\n", WEXITSTATUS(status));
    }
}