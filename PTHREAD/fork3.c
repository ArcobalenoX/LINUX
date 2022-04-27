#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void m()
{
	printf("clean m\n");
}

void n()
{
	printf("clean n\n");
}

int func()
{
	//atexit(n);
	atexit(m);
	printf("func\n");
	//_exit(0);
	//exit(0);
	return 0;
}

int main()
{
	int stauts=func();
	
	int ret = fork();//先返回>0,再返回==0
	if(ret ==0)
	{	
		printf("child:----%d\n",getpid());
		printf("child:====%d\n",getppid());
		
		//pause();//暂停
	}
	else if(ret >0)
	{
		printf("ret=%d\n",ret);//子进程进程号
		printf("parent:----%d\n",getpid());
		printf("parent:====%d\n",getppid());
		
		
	}
	//pause();//向自己进程发送SIGSTP信号:暂停
	printf("(%d)end\n",getpid());
	printf("%d\n\n\n",ret);
	
	exit(0);
}

