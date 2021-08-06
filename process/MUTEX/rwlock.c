/********std header**********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
#include <errno.h>

/**********pthread header*************/
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

char buf[50];

pthread_rwlock_t rwlock=PTHREAD_RWLOCK_INITIALIZER;

void  mypri(char *buf)
{
    int i = 0;

    while(buf[i]!='\0')
    {
        putchar(buf[i++]);
        usleep(1000);
    }
}

void * routine (void *arg)
{

    int i=10;
    while(i--)
    {
        pthread_rwlock_rdlock(&rwlock);
        mypri(buf);
        pthread_rwlock_unlock(&rwlock);
    }

}


int main(int argc,char **argv)
{

    //  mutex=PTHREAD_MUTEX_INITIALIZER;
    //  pthread_mutex_init(&mutex,NULL);


    /*********thread create**********/
    pthread_t tid;
    pthread_create(&tid,NULL,routine,NULL);


    int i=100;
    while(i--)
    {

        pthread_rwlock_wrlock(&rwlock);
        strcpy(buf,"123456789\n");
        usleep(2000);
        pthread_rwlock_unlock(&rwlock);
		
        pthread_rwlock_wrlock(&rwlock);
        strcpy(buf,"abcdefghi\n");
        usleep(2000);
        pthread_rwlock_unlock(&rwlock);

    }



    /********thread join************/
    pthread_join(tid,NULL);

    pthread_rwlock_destroy(&rwlock);


    return 0;
}//end of te main


