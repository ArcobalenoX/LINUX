#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>
#include<unistd.h>
#include<errno.h>


int main()
{

    key_t keyid=ftok("./",2);
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




#ifdef SND

    char buf[24];
    while(1)
    {
        bzero(buf,24);
        //memset(buf,0,24);
        scanf("%s",buf);
        //fgets(buf,24,stdin);
        strcpy(shmaddr,buf);
        if(strncmp(shmaddr,"quit",4)==0)
        {

            struct shmid_ds shmidds;
            shmctl(shmid,IPC_STAT,&shmidds);
            printf("shm segsz=%lu  shm_cpid=%d  shm_lpid=%d\n",\
                   shmidds.shm_segsz,shmidds.shm_cpid,shmidds.shm_lpid);

            struct shminfo  shminfo;
            shmctl(shmid,IPC_INFO, (struct shmid_ds*)&shminfo);
            printf("IPC_INFO:  shmmax=%lu    shmmin==%lu\nshmmni==%lu   shmseg=%lu   shmall=%lu \n",\
                   shminfo.shmmax,shminfo.shmmin,shminfo.shmmni,shminfo.shmseg,shminfo.shmall);

            struct shm_info  shminfo2;
            shmctl(shmid,SHM_INFO, (struct shmid_ds*)&shminfo2);
            printf("SHM_INOF:  shminfo used_ids=%d  shm_tot=%lu  shm_rss=%lu shm_swp==%lu\n",\
                   shminfo2.used_ids,shminfo2.shm_tot,shminfo2.shm_rss,shminfo2.shm_swp);

            break;
        }

    }


#elif defined RCV

    char buf[24];
    while(1)
    {
        sleep(3);
        bzero(buf,24);
        strcpy(buf,shmaddr);
        printf("shmdata= %s\n",buf);
        if(strncmp(shmaddr,"quit",4)==0)
        {
            bzero(buf,24);
            break;
        }
    }


#endif

    shmdt(shmaddr);
    shmctl(shmid,IPC_RMID,NULL);


    return 0;
}