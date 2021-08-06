#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ipc.h>

#define FIFO_PATH "/home/rokudou/fifo"
int main()
{
//创建管道文件
    if(access(FIFO_PATH,F_OK))
    {
        if(mkfifo(FIFO_PATH,0644|O_CREAT|O_EXCL)==-1)
        {
            printf("~/pipe file exist\n");
        }
    }
    int fd = open(FIFO_PATH,O_RDWR);
    if(fd==-1)
    {
        perror("open failed\n");
        return -1;
    }

    char buf[20]="";
    while(1)
    {
        puts("input");
        gets(buf);
		write(fd,buf,20);
        if(strcmp(buf,"quit")==0)
			break;
    }
    close(fd);

    return 0;
}