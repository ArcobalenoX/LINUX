#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include<unistd.h>
#include<string.h>

void * routine1(void *arg)
{
    pid_t pid =getpid();
    pthread_t tid = pthread_self();
    int no = *(int *)arg;
    int time=10;
    printf("%d pthread:pid=%u----tid=%lu \n ",no,pid,tid);

    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);//打开被取消功能
    //  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);//立即取消
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);//遇到取消点函数取消

    while(time--)
    {
        sleep(1);
        printf("%d pthread:times=%d \n ",no,time);
    }

    pthread_exit("pthread 1 byself exit");

}

void * routine2(void *arg)
{
    int no = *(int *)arg;
    int time=5;
    printf("%d pthread:pid=%u----tid=%lu \n ",no,getpid(),pthread_self());

    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);//关闭被取消功能

    while(time--)
    {
        sleep(1);
        printf("%d pthread:times=%d \n ",no,time);
    }
    //pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
    //pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

    pthread_exit("pthread 2 byself exit");

}


int main()
{
    char buf[10];
    printf("main start:pid=%u----tid=%lu \n ",getpid(),pthread_self());


    pthread_t tid1,tid2;

    pthread_attr_t attr;
    pthread_attr_init(&attr);//初始化attr结构体
    //修改attr结构体
    //getdetachstate(&attr)
    // pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED); 	//分离
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);	//结合

    int arg1=1;
    int ret = pthread_create(&tid1,&attr,routine1,&arg1);//线程创建，配置属性，函数及函数传参
    if(ret!=0)
    {
        puts("pthread_create fail ");
        exit( -1);
    }

    int arg2=2;
    ret = pthread_create(&tid2,NULL,routine2,&arg2);
    if(ret!=0)
    {
        puts("pthread_create fail ");
        exit(-1);
    }
    pthread_attr_destroy(&attr);	//销毁attr结构体
    //pthread_detach(tid1);//分离
    //pthread_join(tid1,NULL);//结合，tid1结束后继续


    //sleep(11);
    printf("end input\n");
    while(1)
    {
        scanf("%s",buf);
        if(strncmp(buf,"q",1)==0)
        {
            pthread_cancel(tid1);//取消 pthread_exit不返回join(buff)
            pthread_cancel(tid2);//取消 pthread_exit不返回join(buff)
            break;
        }

        else
        {
            void *buff;
            pthread_join(tid1,&buff);
            puts((char*)buff);
            pthread_join(tid2,&buff);
            puts((char*)buff);

        }
    }

    return 0;
}