#include<stdio.h>
#include<unistd.h>

int main()
{
	int fd[2];
	int ret = pipe(fd);
	if(ret==-1)
	{
	
		return-1;
	}
	
	ret=fork();
	if(ret>0)
	{
		char buf[20]={0};
		
		read(fd[0],buf,20);
		printf("buf1=%s \n ",buf);
		sleep(1);
		char buf2[20]={0};	
		read(fd[0],buf2,20);
		printf("buf2=%s \n ",buf);
	
	
	
	
	
	}
	
	else if(ret==0)
	{
		char name[20]="arcobaleno xxx";
		write(fd[1],name,20);
		if(fork()==0)
		{
			
			char name[20]="ro";
			write(fd[1],name,20);
		}
		
	}
	close(fd[0]);
	close(fd[1]);
	
	return 0;
}