#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>


int main(int argc,char*argv[])
{
	FILE *fp=fopen("./new.txt","w+");
	
	pid_t pid=fork();
	if(pid==-1)
	{
		exit(-1);
	}
	if(pid>0)
	{
		
		char buf[]="hello \n";
		
		printf("return PID=%d\n",pid);
		printf("PID=%d\n",getpid());
		printf("PPID=%d\n",getppid());
		fwrite(buf,10,1,fp);
		printf("父进程写入完成\n");
		fclose(fp);
		pause();
		
	}
	if(pid==0)
	{
		sleep(1);
		fseek(fp,0,SEEK_SET);
		char buf[10];
		printf("PID=%d\n",getpid());
		printf("PPID=%d\n",getppid());
		fread(buf,10,1,fp);
		printf("子进程读出%s\n",buf);
		fclose(fp);
		pause();
	}
	
	
	
	return 0;
}