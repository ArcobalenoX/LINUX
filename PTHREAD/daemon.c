#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

int main()
{
	//1.忽略 SIGHUP的信号
	signal(SIGHUP,SIG_IGN);
	
	//2.创建子进程,并且父进程退出
	int a=fork();
	if(a>0)
		exit(0);
	
	//3.创建新的会话
	setsid();
	
	//4.创建子进程,并且父进程退出
	a=fork();
	if(a>0)
		exit(0);
	
	//5.创建一个新的会话分组
	setpgrp();
	
	//6.关闭之前所有打开的文件描述符
	int i;
	int max_fd = sysconf(_SC_OPEN_MAX);//返回被打开的文件描述符的最大值+1
	for(i=0;i<max_fd;i++)
		close(i);
	
	//7.消除所有文件权限
	umask(0);
	
	//8.修改工作路径
	chdir("/Downloads");
	
	while(1)
	{
		openlog("daemon_test",LOG_CONS|LOG_PID,LOG_DAEMON);
		syslog(LOG_DAEMON,"I am a daemon AAA！");
		
		sleep(1);//延时1s
		
		//syslog(LOG_DAEMON,"I am a daemon BBB！");
	}
	
	
	return 0;
}




