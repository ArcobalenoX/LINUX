#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/wait.h>


void WAIT(void)
{
	int status,ret;
	ret = wait(&status);
	//ret = waitpid(p,status,0);
	printf("父进程\n");
	if(ret ==-1)
	{
		perror("wait?");
	}	
	else if(WIFEXITED(status))
	{
		printf("child PID:%d  exit:%d\n",ret,WEXITSTATUS(status));
	}
	else if( WIFSIGNALED(status))
	{
		printf("child PID:%d  exit:%d\n",ret,WTERMSIG(status));
	}

	
	
}
void pri(void){
	puts("i am child , will exit");
	sleep(5);
#ifdef _EXIT
	_exit(7);
#else 	
	exit(3);
#endif
}

void atexit_fun(void)
{
	printf("atexit be call\n");
}

int main(int argc,char*argv[])
{
	
	pid_t p=fork();
	if(p==-1)
	{
		exit(-1);
	}
	if(p>0)
	{
			
		printf("父进程\n");
		printf("return child PID=%d\n",p);
		printf("PID=%d\n",getpid());
		printf("PPID=%d\n",getppid());
		
		WAIT();
		
		
		//exit(0);
		
	}
	if(p==0)
	{
		//sleep(1);
		
		printf("子进程\n");
		printf("PID=%d\n",getpid());
		printf("PPID=%d\n",getppid());
		//exit(0);
		atexit(&atexit_fun);
		pri();
		//pause();
	}
	
	
	
	return 0;
}