#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<pthread.h>
#include<signal.h>

char buf[10];
sem_t sem;
void * routine(void* arg)
{
    while(1)
    {
        sem_wait(&sem);//V操作，信号量-1
        puts(buf);
        if(!strncmp(buf,"quit",4))
            break;
        bzero(buf,10);
    }
    bzero(buf,10);
    pthread_exit(NULL);

}

void handler()
{
    puts("ctrl^c exit");
    sem_destroy(&sem);
    exit(-1);
}

int main()
{
    signal(2,&handler);//绑定 ctrl+c (2号) 信号


    sem_init(&sem,0,0);//初始化信号量为0
    pthread_t tid;
    pthread_create(&tid,NULL,routine,NULL);//创建routine执行线程

    while(1)
    {
        scanf("%s",buf);
        sem_post(&sem);//P操作 信号量+1
        if(!strncmp(buf,"quit",4))
            break;
    }

    pthread_join(tid,NULL);//等待线程退出

    return 0;
}