/**
*
*	@File Name:shineiji.c
*	@Author:岳秀超 17691051169
*	@Version:1.0
*	@Brief:task_ui
*	@Date:2019.5.28
*
**/

#include "process.h"

//非阻塞检测键盘输入
static int get_char(void)
{
    fd_set rfds;
    struct timeval tv;
    int ch=0;
    FD_ZERO(&rfds);
    FD_SET(0,&rfds);
    tv.tv_sec=0;
    tv.tv_usec=1;
    if(select(1,&rfds,NULL,NULL,&tv)>0)
    {
        ch=getchar();
    }
    return ch;
}

static void change_state(int fd)
{
    char buf[50];
    memset(buf,0,50);
    strcpy(buf,"quit");
    int nbyte = write(fd,buf,strlen(buf));
    printf("%d byte writen\n",nbyte);
    printf("send change_state ok\n");
}
int deal(int fd)
{
    char buf[50];
    memset(buf,0,50);
    int nbyte = read(fd,buf,sizeof(buf));
    if(strncmp(buf,"quit",4)==0)
    {
        printf("task ui recv quit ok\n");
        return 0;
    }
}
int main(int argc,char **argv)
{
    int ch=0;
    int ret;
    //创建fifo
    if(access(FIFO_PATH1,F_OK)!=0)
    {
        ret = mkfifo(FIFO_PATH1,O_CREAT|0666);
        if(ret==-1)
        {
            perror("mkfifo1");
            exit(-1);
        }
    }
    //读取fifo
    int fdr = open(FIFO_PATH1,O_RDWR|O_NONBLOCK,0);
    if(fdr == -1)
    {
        perror("open fifo1");
        exit(-1);
    }

    //创建fifo
    if(access(FIFO_PATH2,F_OK)!=0)
    {
        ret = mkfifo(FIFO_PATH2,O_CREAT|0666);
        if(ret==-1)
        {
            perror("mkfifo2");
            exit(-1);
        }
    }
    //读取fifo
    int fdw = open(FIFO_PATH2,O_RDWR|O_NONBLOCK,0);
    if(fdw == -1)
    {
        perror("open fifo2 ");
        exit(-1);
    }



    char buf[50];
    int nbyte;
    while(1)
    {
        if(deal(fdr)==0)
            break;
        ch=get_char();
        if(ch=='q')
        {
            change_state(fdw);
        }
        else if(ch=='c')
        {
            break;
        }
        else if(ch=='s')
        {
            printf("input:	");
            memset(buf,0,50);
            scanf("%s",buf);
            nbyte = write(fdw,buf,strlen(buf));
            printf("%d byte writen--%s\n",nbyte,buf);

        }



    }

    close(fdr);
    close(fdw);
    return 0;
}//end of te main
