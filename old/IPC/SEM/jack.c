#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/sem.h>

union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
						   (Linux-specific) */
};

//���ź���id�еĵ�semnum���ź������г�ʼ��,��ʼֵΪval
void sem_init(int semid,int semnum,int val)
{
	union semun a;
	a.val = val;
	semctl(semid,semnum,SETVAL,a);
}

//�ź���p����
void sem_p(int semid,int semnum)
{
	struct sembuf sops[1];
	sops[0].sem_num = semnum;	//��Ҫ�����ĵڼ����ź���
	sops[0].sem_op = -1;			//�����ź���
	sops[0].sem_flg= 0;				//�ź�������ģʽ
	if(semop(semid,sops,1)==-1)			//����1���ź���
	{
			perror("semop failed");
	}
}

//�ź���v����
void sem_v(int semid,int semnum)
{
	struct sembuf sops[1];
	sops[0].sem_num = semnum;	//��Ҫ�����ĵڼ����ź���
	sops[0].sem_op = 1;			//�ͷ��ź���
	sops[0].sem_flg= 0	;			//�ź�������ģʽ
	semop(semid,sops,1);			//����1���ź���
}


int main()
{
	//������ֵ
	key_t keyid = ftok("./",0);
	if(keyid == -1)
	{
		perror("ftok faied");
		return -1;
	}
	
	//���ں����빲���ڴ�
	int shmid = shmget(keyid,1024,IPC_CREAT|0666);	
	if(shmid == -1)
	{
		perror("shmget failed");
		return -1;
	}
	
	//���ں��й����ڴ�ӳ�䵽Ӧ�ò�Ŀռ���
	char* shmaddr =shmat(shmid,NULL,0);
	if(shmaddr == (void*)-1)
	{
		perror("shmat failed");
		return -1;
	}
	
	
	//������ֵ���ź���ʹ��,��ʱ�ļ�ֵҪ������ͬ��
	key_t sem_keyid = ftok("./",1);
	if(sem_keyid == -1)
	{
		perror("ftok faied");
		return -1;
	}
	
	//�����ź�������ʼ��
	int semid = semget(sem_keyid,2,IPC_CREAT|0666 );
	if(semid == -1)
	{
		perror("semgetfailed");
	}
	else 
	{
		sem_init(semid,0,1);
		sem_init(semid,1,0);
	}
	
	//�����ڴ�ͨ��
	char sendbuf[1024];
	while(1)
	{
		//�����ź���1һ��
		sem_p(semid,0);
		printf("sem_p 0 ok\n");
		
		bzero(sendbuf,1024);
		scanf("%s",sendbuf);
		strcpy(shmaddr,sendbuf);
		if(strncmp(shmaddr,"88",2)==0)
			break;
		
		//�ͷ��ź���2һ��
		sem_v(semid,1);
		printf("sem_v 1 ok\n");
	}
	
	//ɾ���ź���
	semctl(semid,IPC_RMID,0);
	semctl(semid,IPC_RMID,1);
	//�ͷ�Ӧ�ÿռ��ӳ���ڴ�
	shmdt(shmaddr);
	
	//ɾ�������ڴ�
	shmctl(shmid,IPC_RMID,NULL);
	
	
	return 0;
}
