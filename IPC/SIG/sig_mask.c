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
	 
	//����ÿ���źŶ�ִ���Ӻ���
	int i=1;
	for(i=1;i<65;i++)
	{
		if(i==32||i==33||i==9||i==19)
			continue;
		
		//���õ����յ��źű��Ϊi��ʱ��,ִ��func����
		signal(i,&func);
	}
	
	sigset_t newset;
	
	//�����е��źŶ���ӵ�������,SIGKILL��SIGSTOP����Ч��
	sigfillset(&newset);
	
	//���������е��ź�
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