#include <ctype.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h> //wait関数を含む
#include <unistd.h> //fork,exec関数を含む  pid_t型を含む

#define BUFSIZE 1024
#define DEFAULT_MAX_ARGC 10
#define TOK_DELIM " \t\r\n\a"

int proc_cnt = 0;
pid_t foreground_pid;
void sigchld_wait(int sig) {
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);
    printf("[%d] %d exited with status %d\n", proc_cnt, pid,
           WEXITSTATUS(status));
}

void sigint_ignore(int sig) {}

void sigint_killchlid(int sig) { kill(foreground_pid, SIGINT); }

int main(void) {
    char input[BUFSIZE];

    if (signal(SIGCHLD, sigchld_wait) == SIG_ERR) {
        fprintf(stderr, "rcsh: signal(SIGCHLD) failed\n");
        exit(1);
    }

    if (signal(SIGINT, sigint_ignore) == SIG_ERR) {
        fprintf(stderr, "rcsh: signal(SIGINT) failed\n");
    }

    while (1) {
        //プロンプト表示および入力
        printf("rcsh> ");
        if (fgets(input, BUFSIZE, stdin) == NULL) break;
        input[strlen(input) - 1] = '\0';
        
        //バックグラウンド実行かどうかを決定
        //入力に&があればtrueを代入
        bool exec_bg = strchr(input, '&') != NULL;
        
        //引数の個数とコマンド保存用文字列配列の宣言
        int argc = 0, max_argc = DEFAULT_MAX_ARGC;
        char **argv = calloc(DEFAULT_MAX_ARGC, sizeof(char *));//ポインタを要素に含むのでダブルポインタ

        // strtokは1回目の呼び出しではTOK_DELIMを一切含まない最初の部分をinputから切り出す
        //この際word直後のTOK_DELIM文字は\0に置き換えられる
        //strtokは1回目の呼び出しで分解対象の文字列を指定，以降NULLを指定
        char *word = strtok(input, TOK_DELIM);
        while (word != NULL) {
            argv[argc++] = word;
            //引数の個数が配列の要素数より多かった時の対処
            if (argc >= max_argc) {
                max_argc *= 2;
                // reallocは第1引数の内容をコピーした新しい領域を返す.
                argv = realloc(argv, max_argc * sizeof(char *));
                if (argv == NULL) {
                    fprintf(stderr, "rcsh: allocation error\n");
                    exit(1);
                }
            }
            // 2回目以降はstrtokが1回目に呼び出した文字列を保持しているためNULLを与える
            word = strtok(NULL, TOK_DELIM);
        }

        //コマンドがなければcontinue
        if (argc < 1) continue;

        //&があればこれが引数として渡るのを防ぐためargcを減らしておく
        if (exec_bg) argc--;

        //念のため配列終端をNULLで置いておく
        argv[argc] = NULL;

        // exitコマンド
        //第一引数がexitかどうかを判定
        if (strcmp(argv[0], "exit") == 0) {
            if (argc > 2) {
                fprintf(stderr, "exit: too many arguments\n");
                continue;
            }
            if (argc == 2) {
                return atoi(argv[1]);
            }
            return 0;
        }

        //プロセスをフォークして子プロセスを生成
        pid_t pid = fork();
        //失敗した場合親プロセスに-1が返される
        if (pid < 0) {
            perror("rcsh: ");
            exit(1);
        }
        //forkに成功したら子プロセスには0が返る
        if (pid == 0) {
            setpgid(0, 0);
            execvp(argv[0], argv);
            perror("rcsh: ");
            exit(1);
        }
        
        int status;
        if (exec_bg) {
            printf("[%d] %d\n", ++proc_cnt, pid);
        } else {
            foreground_pid = pid;
            signal(SIGINT, SIG_IGN);
            if (signal(SIGINT, sigint_killchlid) == SIG_ERR) {
                fprintf(stderr, "rcsh: signal(SIGINT) failed\n");
            }
            wait(&status);
            printf("Child process exited with status %d\n",
                   WEXITSTATUS(status));
        }
        //借りたものは返す.
        free(argv);
    }
}

/*-------------------------------------------
-pid_t fork()
プロセスをフォークして子プロセスを生成する．
返り値はPIDである．PIDは親プロセス側では子プロセスのPIDが，子プロセス側では0が返る．

-int execv(char *path, char* argv[])
execシステムコールを発行し，新しいプロセスイメージに置き換わる．
pathには実行するバイナリを，argvには引数を指定する(NULLポインタで終了する必要がある)．
execには様々なフロントエンドがある．他の関数(execl, execvpなど)については`man 3 exec`などを参照．
execはプロセスイメージを置き換えるため返り値は本来返らないはずである．エラーが発生した場合は-1が返り，errnoに内容が設定される．

-pid_t wait(int *status)
子プロセスのいずれかが終了するまで待機する．
SIGCHILDを受け取ったら子プロセスのリソースを解放し，statusに状態情報を格納する．状態情報はマクロによって内容を知ることができる．マクロの情報は`man 2 wait`を参照
返り値は終了した子プロセスのPIDとなる．エラーの場合-1を返す．

-WEXITSTATUS(status)
子プロセスの終了ステータスを返す

-int setpgid(pid_t pid, pid_t pgid)
子プロセスのフォーク後に子プロセスのプロセスグループを変更する．
第1引数には移動するプロセスのIDを指定する
第2引数には移動先のプロセスグループのリーダーのPGIDを指定する
どちらも0を指定することで関数を呼び出したプロセスのPIDを指定できる
成功すれば0，失敗すれば－1を返したうえでerrnoを設定する．
--------------------------------------------*/

/*-------------------------------------------
-char *strchr(const char *s,int c)
文字列の先頭から文字を検索
文字列sから文字cを探し，見つかったらその場所を返す．なかったらNULLを返す．

-int strcmp(const char *s1, const char *s2)
文字列s1と文字列s2(の文字コード)を比較し，s1-s2の正負を返す
要はs1とs2が共通なら0を返す
--------------------------------------------*/