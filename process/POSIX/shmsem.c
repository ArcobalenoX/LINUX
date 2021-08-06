#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sem1aphore.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<errno.h>


int main()
{
    key_t keyid=ftok("./",1);
    if (keyid == -1)
    {
        perror("ftok fail");
        return -1;
    }
    else printf("keyid= 0x%x\n",keyid);
    //向内核申请共享内存
    int shmid=shmget(keyid,1024,IPC_CREAT|0666);
    if (shmid == -1)
    {
        perror("shmget fail");
        return -1;
    }
    else printf("shmid= %d\n",shmid);
    //将内核中共享内存映射到应用层的空间中
    char * shmaddr = shmat(shmid,NULL,0);
    if(shmaddr==NULL)
    {
        perror("shmat fail");
        return -1;
    }
    sem1_t * sem11 = sem1_open("/sem11",O_CREAT,0666,0);

    sem1_t * sem12  = sem1_open("/sem12",O_CREAT,0666,1);


#ifdef SND

    char buf[24];
    while(1)
    {

        scanf("%s",buf);
        sem1_post(sem1);
        strcpy(shmaddr,buf);
        if(!strncmp(buf,"quit",4))
            break;

    }


#elif defined RCV

    char buf[24];
    while(1)
    {
        sem1_wait(sem1);
        strcpy(buf,shmaddr);
        puts(buf);
        if(!strncmp(buf,"quit",4))
            break;
        //   bzero(buf,24);
    }


#endif
    sem1_close(sem1);
    //sem1_unlink(sem1);
    shmdt(shmaddr);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}