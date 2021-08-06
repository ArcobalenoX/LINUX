#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<pthread.h>
#include<signal.h>

char buf[10];
sem_t *  sem1=NULL;
sem_t *  sem2=NULL;
void * routine(void* arg)
{
    while(1)
    {
        sem_wait(sem1);//V操作，信号量-1
        puts(buf);
        sem_post(sem2);
        if(!strncmp(buf,"quit",4))
            break;
        bzero(buf,10);

    }
    pthread_exit(NULL);

}
void handler()
{

    puts("ctrl^c exit");
    sem_close(sem1);
    sem_unlink("/name1");
    exit(-1);
}
int main()
{
    signal(2,&handler);
    sem1  = sem_open("/name1",O_CREAT,0666,0);//初始化信号量为0
    sem2  = sem_open("/name2",O_CREAT,0666,1);
    pthread_t tid;
    pthread_create(&tid,NULL,routine,NULL);

    while(1)
    {
        sem_wait(sem2);
        scanf("%s",buf);
        sem_post(sem1);//P操作 信号量+1

        if(!strncmp(buf,"quit",4))
            break;

    }

    pthread_join(tid,NULL);

    return 0;
}