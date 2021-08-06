#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/sem.h>


union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
						   (Linux-specific) */
};


//对信号量id中的第semnum个信号量进行初始化,初始值为val
void sem_init(int semid,int semnum,int val)
{
	union semun a;
	a.val = val;
	semctl(semid,semnum,SETVAL,a);
}

//信号量p操作
void sem_p(int semid,int semnum)
{
	struct sembuf sops[1];
	sops[0].sem_num = semnum;	//需要操作的第几个信号量
	sops[0].sem_op = -1;			//申请信号量
	sops[0].sem_flg= 0;				//信号量操作模式
	semop(semid,sops,1);			//操作1个信号量
}

//信号量v操作
void sem_v(int semid,int semnum)
{
	struct sembuf sops[1];
	sops[0].sem_num = semnum;	//需要操作的第几个信号量
	sops[0].sem_op = 1;			//释放信号量
	sops[0].sem_flg= 0;			//信号量操作模式
	semop(semid,sops,1);			//操作1个信号量
}
int main()
{
	//创建键值
	key_t keyid = ftok("./",0);
	if(keyid == -1)
	{
		perror("ftok faied");
		return -1;
	}
	
	//向内核申请共享内存
	int shmid = shmget(keyid,1024,IPC_CREAT |0666);	
	if(shmid == -1)
	{
		perror("shmget failed");
		return -1;
	}
	
	//将内核中共享内存映射到应用层的空间中
	char* shmaddr =shmat(shmid,NULL,0);
	if(shmaddr == (void*)-1)
	{
		perror("shmat failed");
		return -1;
	}
	
	
	//创建键值给信号量使用,这时的键值要创建不同的
	key_t sem_keyid = ftok("./",1);
	if(sem_keyid == -1)
	{
		perror("ftok faied");
		return -1;
	}
	
	//创建信号量并初始化
	int semid = semget(sem_keyid,2,IPC_CREAT |0666);
	if(semid == -1)
	{
		perror("semgetfailed");
	}
	//这里不需要再初始化,否则会改变信号量的值
	
	
	
	//共享内存通信
	char recvbuf[1024];
	while(1)
	{
		sem_p(semid,1);
		printf("sem_p 1 ok\n");
		
		sleep(1);
		bzero(recvbuf,1024);
		strcpy(recvbuf,shmaddr);
		printf("recvbuf=%s\n",recvbuf);
		printf("recvbuf=%s\n",shmaddr);
		
		if(strncmp(shmaddr,"88",2)==0)
		{
			break;
		}
		
		sem_v(semid,0);
		printf("sem_v 0 ok\n");
	}

	
	//释放应用空间的映射内存
	shmdt(shmaddr);
	
	//删除共享内存
	shmctl(shmid,IPC_RMID,NULL);
	

	return 0;
}
