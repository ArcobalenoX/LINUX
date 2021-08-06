#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<pthread.h>

char buf[10];
int flag;
void * routine(void* arg)
{
    while(1)
    {
        if(flag==1)
        {
            flag=0;

            puts(buf);
            if(!strncmp(buf,"quit",4))
                break;

        }


    }
    pthread_exit(NULL);

}
int main()
{

    pthread_t tid;
    pthread_create(&tid,NULL,routine,NULL);
    bzero(buf,10);
    while(1)
    {
        if(flag==0)
        {
            flag=1;
            scanf("%s",buf);

            if(!strncmp(buf,"quit",4))
                break;
        }

    }

    pthread_join(tid,NULL);


    //sem_unlink(sem);

    return 0;
}