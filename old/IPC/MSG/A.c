#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
//消息队列结构体
struct msgbuf {
    long mtype;       /* 消息的标志位,必须 > 0 */
    char mtext[20];    /* 具体的信息 */
};


struct msgbuf  info;	
struct msgbuf recv;
int msgid;

void *func(void *arg)
{
	printf("recv=%s\n",recv.mtext);
	//if(strcmp(recv.mtext,"88")==0)
	//	break;
	char *str="hello world";
	pthread_exit(str);
}



int main()
{
	info.mtype = 1;		//设置消息的标志为1
	recv.mtype = 2;
	//创建键值
	key_t keyid = ftok(".",1);
	if(keyid == -1)
	{
		perror("ftok failed");
		return -1;
	}	
	//申请消息队列
	msgid = msgget(keyid, IPC_CREAT | 0666);
	if(msgid == -1)
	{
		perror("msgget failed");
		return -1;
	}

	pthread_t tid;		
	pthread_create(&tid,NULL,func,NULL);
	while(1)
	{
		msgrcv(msgid,&recv,20,2,0);
		
		scanf("%s",info.mtext);//输入要发送的消息	
		//发送消息
		msgsnd(msgid,&info, 20,0);	
		if(strcmp(info.mtext,"88")==0)
			break;	
			
	}
		
		
	pthread_join(tid,NULL);
	//删除消息队列
	msgctl(msgid,IPC_RMID,NULL);
	pthread_exit(NULL);	
	//return 0;
}