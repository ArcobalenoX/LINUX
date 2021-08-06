#include <stdio.h>
#include <signal.h>
#include<unistd.h>

void func(int arg)
{
	printf("arg=%d\n",arg);
}

int main()
{
	printf("my getpid()=%d\n",getpid());
	 
	//设置每个信号都执行子函数
	int i=1;
	for(i=1;i<65;i++)
	{
		if(i==32||i==33||i==9||i==19)
			continue;
		
		//设置当接收到信号编号为i的时候,执行func函数
		signal(i,&func);
	}
	
	sigset_t newset;
	
	//把所有的信号都添加到集合中,SIGKILL和SIGSTOP是无效的
	sigfillset(&newset);
	
	//阻塞了所有的信号
	sigprocmask(SIG_BLOCK,&newset,NULL);
	printf("mask OK\n");
	
	sleep(5);
	
	printf("sleep full\n");
	sigprocmask(SIG_UNBLOCK,&newset,NULL);
	printf("unmask OK\n"); 

	while(1)
	{
		sleep(1);
	}
	
	return 0;
}