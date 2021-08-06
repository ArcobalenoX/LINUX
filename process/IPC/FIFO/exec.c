#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
char *const ps_argv[] = {"ps", "-o", "pid, ppid, session, tpgid, comm, NULL"};

char *const ps_envp[] =  {"PATH=/bin:/usr/bin", "TERM=console", NULL};

execl("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);

execv("/bin/ps", ps_argv);

execle("/bin/ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL, ps_envp);

execve("/bin/ps", ps_argv, ps_envp);

execlp("ps", "ps", "-o", "pid,ppid,pgrp,session,tpgid,comm", NULL);

execvp("ps", ps_argv);

*/

extern char **environ;

int main(int argc,char *argv[])
{

    if(strcmp(argv[1],"fifo1")==0)
    {
        char *ps_argv[]= {"fifo1","A123","B456",NULL};
        puts("enter fifo1");

        execl("./fifo1","fifo1",NULL);
        //execlp("./fifo1","fifo1",NULL);

        puts("enter fail");
    }



    if(strcmp(argv[1],"tmp.sh")==0)
    {
        char *ps_argv[]= {"tmp.sh","A123","B456",NULL};
        char *ps_envp[]= {"A=22","B=33",NULL};
        puts("enter tmps..sh");

        execle("./tmp.sh", "tmp.sh", NULL, ps_envp);
        // execve("./tmp.sh", ps_argv, ps_envp);

        puts("enter fail");
    }


    if(strcmp(argv[1],"fifo2")==0)
    {
        char *ps_argv[]= {"fifo2","A123","B456",NULL};
        puts("enter fifo2");

        execv("./fifo2", ps_argv);
        //execvp("./fifo2", ps_argv);
        puts("enter fail");

    }




    return 0;
}