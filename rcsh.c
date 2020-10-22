#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    while (1) {
        char strin[256]="/bin/sleep";

        char* cmd[3];
        cmd[0]=strin;
        cmd[1]="5";
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