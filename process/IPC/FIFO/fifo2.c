#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define FIFO_PATH "/home/rokudou/fifo"

int main()
{
    if(access(FIFO_PATH,F_OK))
    {
        if(mkfifo(FIFO_PATH,644|O_CREAT|O_EXCL)==-1)
        {
            perror("~/pipe file exist");
        }
    }
    int fd = open(FIFO_PATH,O_RDONLY);
    if(fd==-1)
    {
        perror("open failed\n");
        return -1;
    }

    char buf[20]= {0};
    while(1)
    {
        sleep(1);
        read(fd,buf,20);
        if(strcmp(buf,"quit")==0)
            break;
        else
            printf("buf=%s\n",buf);
    }
    close(fd);
    return 0;
}