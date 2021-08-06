#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include<unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

void func_handler(int sig)
{
	printf("recv sig_%d\n",sig);
	
	alarm(3);
	//setitimer(10);
	
}
int main(void)
{
	puts("main is runing>>>>");
	
	signal(14,func_handler);	
	//signal(14,SIG_IGN);
	//signal(14,SIG_DFL);
	raise(14);
	
	pid_t pid=getpid();
	kill(pid,14);
	
	while(1)
	{
		sleep(100);
		puts("????");
	}
	
	return 0;
	
}