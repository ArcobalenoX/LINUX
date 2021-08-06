/********std header**********/
#define _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>

/**********IO header*************/
#define _PG_IO
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

void *routine(void *arg)
{

	int fd = *(int *)arg;

	char buf[30];
	while (1)
	{
		memset(buf, 0, 30);
		int size = Read(fd, buf, 30);

		printf("read:<%d> %s\n", size, buf);

		if (!strncmp(buf, "exit", 4))
		{
			break;
		}
	}

	return NULL;
}

int main(int argc, char **argv)
{

	//1. 打开串口 节点文件
	int fd = Open("/dev/ttySAC1", O_RDWR | O_NOCTTY);

	//2. 初始化串口
	tty_init(fd);

	char buf[30];
	int size;

	pthread_t tid;

	pthread_create(&tid, NULL, routine, (void *)&fd);

	//串口写入
	while (1)
	{

		memset(buf, 0, 30);
		scanf("%s", buf);
		size = Write(fd, buf, strlen(buf));
		printf("write: %d\n", size);

		if (!strncmp(buf, "exit", 4))
		{
			break;
		}
	}

	pthread_join(tid, NULL);

	return 0;
} //end of te main

void tty_init(const int fd)
{

	struct termios tty_opt;

	//1. 初始化结构体（CS8  关闭校验）
	cfmakeraw(&tty_opt);

	//2. 配置 停止位 + 打开接受
	tty_opt.c_cflag &= ~CSTOPB;
	tty_opt.c_cflag |= CREAD;

	//3.配置特殊选项
	tty_opt.c_cc[VMIN] = 16;  //最少字符
	tty_opt.c_cc[VTIME] = 50; //5秒

	//4. 设置波特率
	cfsetspeed(&tty_opt, B115200);

	//5. 初始化串口
	tcsetattr(fd, TCSAFLUSH, &tty_opt);

	return;
}
