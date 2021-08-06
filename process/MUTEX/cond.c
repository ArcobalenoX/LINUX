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
int save=100;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond=PTHREAD_COND_INITIALIZER;


void * routine (void *arg)
{
    int no = (int)arg;
    int i = 0;
    pthread_mutex_lock(&mutex);
	if(save<70)
		pthread_cond_wait(&cond,&mutex);//自动解锁等待自动加锁
    printf("pthread %d is read\n",no);

    while(buf[i]!='\0')
    {
        putchar(buf[i++]);
        usleep(1000);
    }
	save -=10;
	printf("save is %d\n",save);

    pthread_mutex_unlock(&mutex);
	pthread_exit(NULL);

}


int main(int argc,char **argv)
{
    //pthread_mutex_init(&mutex);
    //pthread_cond_init(&cond,NULL);

    /*********thread create**********/
    pthread_t tid[7];
    int i;
    for(i=1; i<7; i++)
    {
        pthread_create(&tid[i],NULL,routine,(void*)i);
    }

    strcpy(buf,"123456789\n");
    puts("after 1s cond unseal");
    sleep(1);//防止线程cond_wait没收到cond
    pthread_cond_broadcast(&cond);
    // pthread_cond_signal(&cond);

    /********thread join************/

    for(i=1; i<7; i++)
    {
        pthread_join(tid[i],NULL);
    }
    /********mutex & cond destroy*******/
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}//end of te main


