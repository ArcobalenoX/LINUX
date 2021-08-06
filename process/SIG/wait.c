#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include<wait.h>
#include<unistd.h>
#include<error.h>
#include<string.h>
void print_exit(int status)
{
    if (WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP
        WCOREDUMP(status) ? ("core file generated") : (""));
#else
    "");
#endif
    else if (WIFSTOPPED(status))
        printf("child stopped, signal number=%d\n", WSTOPSIG(status));
}

void sig_child(int signo)
{
    int status;
    int ret;
    ret = wait(&status);
    printf("pid:%d, res:%d, status=%d, %s\n", getpid(), ret, status, strerror(errno));
    print_exit(status);
}

void sig_usr(int signo)
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGUSR2)
        printf("received SIGUSR2\n");
    else
        printf("received signal %d\n", signo);
}


int main(int argc, char** argv)
{
    pid_t pid;
    int status;
    int ret;
    int remaintime=0;
    struct sigaction act, oact;
    sigset_t oldmask;

    //signal(SIGCHLD, sig_child);
    //signal(SIGUSR1, sig_usr);
    
    act.sa_handler = sig_usr;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0|SA_INTERRUPT;
    sigaction(SIGUSR1, &act, &oact);

    if ((pid=fork()) < 0)
    {
        printf("fork error\n");
        return -1;
    }
    else if (pid == 0)
    {

        printf("child:pid:%d\n", getpid());
        remaintime = sleep(200);
        printf("remiantime=%d\n", remaintime);
        //exit(0);    
        //return 0;
        //
        //sleep(30);//SIGQUIT
    }
    else
    {
        printf("father:pid:%d\n", getpid());
        //while(1)
        //{
        //    sleep(1);
        //    printf("1111\n");
        //}
        ret = wait(&status);
        printf("res:%d, status=%d, %s\n", ret, status, strerror(errno));
        print_exit(status);
    }

    return 0;
}