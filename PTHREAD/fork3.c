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
	
	int ret = fork();//�ȷ���>0,�ٷ���==0
	if(ret ==0)
	{	
		printf("child:----%d\n",getpid());
		printf("child:====%d\n",getppid());
		
		//pause();//��ͣ
	}
	else if(ret >0)
	{
		printf("ret=%d\n",ret);//�ӽ��̽��̺�
		printf("parent:----%d\n",getpid());
		printf("parent:====%d\n",getppid());
		
		
	}
	//pause();//���Լ����̷���SIGSTP�ź�:��ͣ
	printf("(%d)end\n",getpid());
	printf("%d\n\n\n",ret);
	
	exit(0);
}

