/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>

/**********IO header*************/
#define  _PG_IO
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

/*********Packgage function myheader****/
#include "Package.h"


#include <termios.h>
#include <pthread.h>

void tty_init(const int);


void * routine(void * arg){

	int fd = *(int *)arg;

	char buf[30];
	while(1){
		memset(buf, 0, 30);	
		int size = Read(fd, buf, 30);

		printf("tty2 read:<%d> %s\n", size, buf);

		if(!strncmp(buf, "exit", 4)){
			break;
		}
	
	}

	return NULL;
}



int main(int argc,char **argv)
{
		
	//1. 打开串口 节点文件
	int fd = Open("/dev/ttySAC1", O_RDWR|O_NOCTTY);
	int fd2 = Open("/dev/ttySAC2", O_RDWR|O_NOCTTY);
	/* O_NOCTTY
	If pathname refers to a terminal device—see tty(4)—it  will 
	not become  the  process's  controlling terminal even if the process does not have one.*/

	//2. 初始化串口
	tty_init(fd);
	tty_init(fd2);

	char buf[30];
	int size;

	pthread_t  tid;
	pthread_create(&tid, NULL, routine, (void *)&fd2);
	
	//串口写入
	while(1){
		
		memset(buf,0,30);
		scanf("%s",buf);
		size = Write(fd, buf, strlen(buf));//写入串口1
		printf("tty1 write: %d\n",size);

		if(!strncmp(buf, "exit", 4)){
			break;
		}
	}

	pthread_join(tid, NULL);

	return 0;
}//end of te main



void tty_init(const int fd){


	struct termios tty_opt;

	//1. 初始化结构体（CS8  关闭校验）
	cfmakeraw( &tty_opt );

	//2. 配置自定义选项
	tty_opt.c_cflag &= ~CSTOPB;//停止位为1
	tty_opt.c_cflag |= CREAD;//打开读取
	tty_opt.c_cflag &= ~CSIZE;//清除传输位数掩码
	tty_opt.c_cflag |= CS8;//设置传输位数
	tty_opt.c_cflag &= ~CRTSCTS;//关闭流控
	tty_opt.c_cflag &= ~PARENB;//关闭校验
	

	//3.配置特殊选项
	tty_opt.c_cc[VMIN] = 4;//缓冲读取N字节
	tty_opt.c_cc[VTIME] = 50;//延时读取N/10秒

	//4. 设置波特率
	cfsetspeed(&tty_opt, B115200);

	//5. 初始化串口
	tcsetattr(fd, TCSAFLUSH , &tty_opt);

	//6. 刷新缓冲区
	tcflush( fd, TCIOFLUSH );


	return;
}



