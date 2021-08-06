#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

union semun
{
    int val;  /* SETVAL--�����ź�����ֵ */
    struct semid_ds *buf; /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};
static void seminit(int semid, int semnum, int value)
{
    union semun semunion;
    semunion.val = value;
    semctl(semid, semnum, SETVAL, semunion);
	/*semdi ����ID ,semnum ��Ҫ�����ĵڼ����ź�������0��ʼ��, SETVAL �����ź��� , semunion �������ֵ)*/
}

static void sem_p(int semid, int semnum)
{
    struct sembuf op[1];
    op[0].sem_num = semnum;/* �ź������ */
    op[0].sem_op  = -1;/* P������+1�� */
    op[0].sem_flg = 0; /* һ��Ϊ0 */

    semop(semid, op, 1);/*semid ����ID , op �����ṹ��  , 1 ��Ҫ�������ź���������*/
}

static void sem_v(int semid, int semnum)
{
    struct sembuf op[1];
    op[0].sem_num = semnum;
    op[0].sem_op  = +1;/* V������-1��*/
    op[0].sem_flg = 0;

    semop(semid, op, 1);
}


int main()
{
    //������ֵ
    key_t key1 = ftok("./", 1);
    key_t key2 = ftok("./", 2);
    if(key1 == -1||key2 == -1)
    {
        perror("ftok faied");
        return -1;
    }
    //���ں����빲���ڴ�
    int shmid = shmget(key1,128, IPC_CREAT|0644);
    if(shmid == -1)
    {
        perror("shmget failed");
        return -1;
    }
    //���ں��й����ڴ�ӳ�䵽Ӧ�ò�Ŀռ���
    char *shmaddr = shmat(shmid, NULL, 0);
    if(shmaddr == (void*)-1)
    {
        perror("shmat failed");
        return -1;
    }

	//�����ź�������ʼ��
    int semid = semget(key2, 2, IPC_CREAT|IPC_EXCL|0644);
    if(semid == -1 && errno == EEXIST)
    {
        semid = semget(key2, 2, 0644);
    }
    else
    {
        seminit(semid, 0, 0);
        seminit(semid, 1, 1);
    }


#ifdef SND

  
    while(1)
    {

        sem_p(semid, 1);
        fgets(shmaddr,128, stdin);
        sem_v(semid, 0);

        if(strncmp(shmaddr,"quit",4)==0)
            break;
    }

#elif defined RCV

    while(1)
    {
        sem_p(semid, 0);
        printf("from sem: %s", shmaddr);
        sem_v(semid, 1);

        if(strncmp(shmaddr,"quit",4)==0)
            break;
    }

#endif
    //�ͷ�Ӧ�ÿռ��ӳ���ڴ�
    shmdt(shmaddr);

    //ɾ���ź���
    shmctl(shmid,IPC_RMID,NULL);
    //semctl(semid,IPC_RMID,NULL);

    return 0;
}
