#include <stdio.h>
#include <signal.h>
#include<stdlib.h>

void func(int arg)
{
	printf("arg=%d\n",arg);
}

int main(int argc,char *argv[])
{
	int pid = atoi(argv[1]);
	//���ӽ��̷������е��ź�
	int i=1;
	for(i=1;i<65;i++)
	{
		if(i==32||i==33||i==9||i==19)
			continue;
		
		kill(pid,i);
	}
	printf("send kill ok\n");
	
	return 0;
}