/**
*
*	@File Name:
*	@Author:岳秀超 17691051169
*	@Version:1.0
*	@Brief:task_phone
*	@Date:2019.5.28
*
**/

#include "process.h"
#define TIME_NEXT	50

enum TASK_PHONE_STATE
{
    TASK_PHONE_STATE_NONE=0,
    TASK_PHONE_STATE_RING,
    TASK_PHONE_STATE_TALK,
    TASK_PHONE_STATE_HANGUP,
};
int phone_state =TASK_PHONE_STATE_NONE;
//设置通话状态
void set_state(int state)
{
    phone_state=state;
}
//获取通话状态
int get_state(void)
{
    return phone_state;
}
//非阻塞检测键盘输入
static int get_chars(int fd)
{
    fd_set rfds;
    struct timeval tv;
    int nbyte=0;
    FD_ZERO(&rfds);
    FD_SET(1,&rfds);
    tv.tv_sec=0;
    tv.tv_usec=1;
    char buf[50];
    if(select(2,&rfds,NULL,NULL,&tv)>0)
    {
        memset(buf,0,50);
        scanf("%s",buf);
        nbyte = write(fd,buf,strlen(buf));
        printf("%d byte writen--%s\n",nbyte,buf);
    }
    return nbyte;
}

int main(int argc,char **argv)
{
    int time=0;
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
    int fdw = open(FIFO_PATH1,O_RDWR|O_NONBLOCK,0);
    if(fdw == -1)
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
    int fdr = open(FIFO_PATH2,O_RDWR|O_NONBLOCK,0);
    if(fdr == -1)
    {
        perror("open fifo2");
        exit(-1);
    }

    char buf[50];
    int nbyte;
    while(1)
    {
        time++;
        memset(buf,0,50);
        nbyte = read(fdr,buf,sizeof(buf));
        if(nbyte >0)
        {
            printf("%d byte read--%s\n",nbyte,buf);
            set_state(TASK_PHONE_STATE_RING);
            time=0;
        }
        //每5s轮询一次
        else if(time>=TIME_NEXT)
        {
            time=0;
            if(get_state()==TASK_PHONE_STATE_RING)
            {
                set_state(TASK_PHONE_STATE_TALK);
            }
            else if(get_state()==TASK_PHONE_STATE_TALK)
            {
                set_state(TASK_PHONE_STATE_HANGUP);
            }
            else
            {
                set_state(TASK_PHONE_STATE_RING);
            }
            printf("Current state is %d\n",get_state());
        }



        //判断是否为挂断
        if(get_state()==TASK_PHONE_STATE_HANGUP)
        {

            //写入挂断状态给UI任务
            memset(buf,0,50);
            strcpy(buf,"quit");
            nbyte = write(fdw,buf,strlen(buf));
            printf("%d byte writen--%s\n",nbyte,buf);
            break;
        }

        get_chars(fdw);
        usleep(100*1000);//100ms
    }
    close(fdr);
    close(fdw);
    return 0;
}//end of te main


