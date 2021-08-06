#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<signal.h>

void sigfun(int n)
{
    puts("recv sig13");
}
int
main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;

    // if (argc != 2) {
    // fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    // exit(EXIT_FAILURE);
    // }

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (cpid == 0)      /* Child reads from pipe */
    {
        close(pipefd[1]);          /* Close unused write end */
        //close(pipefd[0]);
        while (read(pipefd[0], &buf, 1) > 0)
            write(STDOUT_FILENO, &buf, 1);

        write(STDOUT_FILENO, "\n", 1);
        //close(pipefd[0]);
        exit(EXIT_SUCCESS);
    }
    else                /* Parent writes argv[1] to pipe */
    {

        char buf[50]= {0};
        // sleep(3);

        close(pipefd[0]);          /* Close unused read end */
        //close(pipefd[1]);


        // signal(13,SIG_IGN);//write 发送 13信号SIGPIPE
        signal(13,sigfun);

        gets(buf);
        puts("hello1");

        int nbyte = write(pipefd[1], buf, strlen(buf));

        printf("write:%d byte\n",nbyte);

        puts("hello2");
        //close(pipefd[1]);          /* Reader will see EOF */


        wait(NULL);                /* Wait for child */
        exit(EXIT_SUCCESS);
    }
}

