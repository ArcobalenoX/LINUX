#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

//消息队列结构体
struct msgbuf {
    long mtype;       /* 消息的标志位,必须 > 0 */
    char mtext[20];    /* 具体的信息 */
};

int main()
{
	//创建键值
	key_t keyid = ftok(".",1);
	if(keyid == -1)
	{
		perror("ftok failed");
		return -1;
	}
	
	//申请消息队列
	int msgid = msgget(keyid, IPC_CREAT | 0666);
	if(msgid == -1)
	{
		perror("msgget failed");
		return -1;
	}
	
	struct msgbuf recv;
	
	while(1)
	{
		//接收消息,第四个参数与发送方的标志位有关
		msgrcv(msgid,&recv,20,2,0);
		printf("recv=%s\n",recv.mtext);
		if(strcmp(recv.mtext,"88")==0)
			break;
	}
	
	
	//删除消息队列
	msgctl(msgid,IPC_RMID,NULL);
	
	return 0;
}