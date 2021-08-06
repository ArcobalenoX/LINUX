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
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>

/**********IPC header***********/
#define  _PG_IPC
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <unistd.h>

/*********Packgage function myheader****/
#include "Package.h"


#define FIFO_FILE	"/tmp/myfifo"

int main(int argc,char **argv)
{

	//1. 创建管道文件 + 打开
	if(access(FIFO_FILE, F_OK)){//不存在
		
		Mkfifo(FIFO_FILE, O_CREAT|0666);
	}

	int fd = Open(FIFO_FILE, O_RDWR);


	//2. 播放视频
	system("mplayer  -quiet -zoom -x 800 -y 480  \
	-slave -input file=/tmp/myfifo -loop 0 -playlist ./yinshipin &");


	//3. 管道控制

	char tmp[10];

	while(1){
		
		scanf("%s",tmp);

		if(!strncmp(tmp,"seek+", 5)){
		
			write(fd, "seek 10\n",8);

		}else if(!strncmp(tmp,"Q", 1)){
		
			write(fd, "quit\n",5);
			break;

		}else if(!strncmp(tmp,"help", 4)){
		
			printf("seek+ : 快进10s\n");
			printf("help  : 帮助\n");
		}
	
	}

	return 0;
}//end of te main


