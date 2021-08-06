#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>

struct msgbuf
{
    long mtype;
    char buf[10];

};
#define CH1 1
#define CH2 2



int main(int argc,char **argv)
{

    key_t key=ftok("./",1);
    if(key== -1)
    {
        perror("ftok failed");
        return -1;
    }
    else
        printf("key=%x\n",key);

    int msgid=msgget(key,IPC_CREAT|0666);
    if(msgid == -1)
    {
        perror("msgget failed");
        return -1;
    }
    else
        printf("msgid=%d\n",msgid);



    struct msgbuf BUF1;
    struct msgbuf BUF2;

#ifdef SND

    BUF1.mtype=1;
    BUF2.mtype=2;
    while(1)
    {

        printf("to send which? input 1 or 2\n");
        char * chanel;
        scanf("%s",chanel);
        if(strncmp(chanel,"1",1)==0)
        {
            puts("input msg to 1");
            scanf("%s",BUF1.buf);
            msgsnd(msgid,&BUF1,sizeof(BUF1),0);
        }

        else if(strncmp(chanel,"2",1)==0)
        {
            puts("input msg to 2");
            scanf("%s",BUF2.buf);
            msgsnd(msgid,&BUF2,sizeof(BUF2),0);


        }
        else if(strncmp(chanel,"q",1)==0)
        {

            struct msginfo Minfo;
            msgctl(msgid,MSG_INFO,(struct msqid_ds *)&Minfo);
            printf("msgmax:%d  msgmnb:%d  msgmni:%d\n",\
                   Minfo.msgmax,Minfo.msgmnb,Minfo.msgmni);

            struct msqid_ds buf;
            msgctl(msgid,MSG_STAT,&buf);
            printf(" __msg_cbytes=%ld  msg_qnum=%ld  msg_qbytes=%ld\n",\
                   buf. __msg_cbytes,buf.msg_qnum,buf.msg_qbytes);


            msgctl(msgid,IPC_RMID,NULL);
            break;
        }


    }


#elif defined RCV
    int pid=fork();
    while(1)
    {
        if(pid==-1)
            perror("fork failed");
        else if(pid==0)
        {
            int ret= msgrcv(msgid,&BUF1,sizeof(BUF1),1,0);
            if(ret== -1)
            {
                puts("msgrcv err");
                return -1;
            }
            else printf("parent recv msg 1 - %dbyte--%s\n",ret,BUF1.buf);

        }
        else if(pid>0)
        {

            int ret= msgrcv(msgid,&BUF2,sizeof(BUF2),2,0);
            if(ret== -1)
            {
                puts("msgrcv err");
                return -1;
            }
            else printf("child recv msg 2 - %d--%s\n",ret,BUF2.buf);

        }

    }

#endif


    return 0;
}