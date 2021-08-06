/********std header**********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
#include <errno.h>
#include<unistd.h>
/**********pthread header*************/
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

/**************global val****************/
char buf[50];
sem_t * mysem=NULL;

void * routine(void *arg)
{

    int semvalue;
    while(1)
    {
        //	sem_getvalue(mysem,&semvalue);
        //printf("before wait:%d\n",semvalue);

        sem_wait(mysem);

        puts(buf);

        //	sem_getvalue(mysem,&semvalue);
        //	printf("after wait:%d\n",semvalue);

        if(strncmp(buf,"exit",4)==0)break;
        bzero(buf,50);
    }

    pthread_exit(NULL);
}



int main(int argc,char **argv)
{
    /******thread create*******/
    pthread_t tid;
    pthread_create(&tid,NULL,routine,NULL);

    /*******sem create && init**********/
    mysem = sem_open("/sem1",O_CREAT,0666,0);
    if(mysem==SEM_FAILED)perror("sem_oepn");

    int semvalue;
    while(1)
    {
        //	usleep(1000);
        //	memset(buf,0,50);
        //	fgets(buf,50,stdin);
        scanf("%s",buf);
        //	sem_getvalue(mysem,&semvalue);
        //	printf("before post:%d\n",semvalue);

        sem_post(mysem);

        //	sem_getvalue(mysem,&semvalue);
        //	printf("after post:%d\n",semvalue);
    }

    /******thread join*******/
    pthread_join(tid,NULL);
	//sem_close(mysem);
    return 0;
}//end of te main


