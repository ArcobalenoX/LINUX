#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t m;


void handler(void *arg)
{
	printf("m over\n");
	pthread_mutex_unlock(&m);
}


//�̺߳���
void *func1(void *arg)
{
	pthread_cleanup_push(handler,NULL);
	pthread_mutex_lock(&m);
	int i=0;
	while(i<5)
	{
		i++;
		sleep(1);
		printf("func1:i=%d\n",i);
	}
	pthread_mutex_unlock(&m);
		pthread_cleanup_pop(0);
}


void *func2(void *arg)
{
	//�ڼ���֮ǰ,���ý����ĺ���
	pthread_cleanup_push(handler,NULL);
	
	pthread_mutex_lock(&m);
	int i=0;
	while(i<5)
	{
		i++;
		sleep(1);
		printf("func2:i=%d\n",i);
	}
	pthread_mutex_unlock(&m);
	
	//������߳����Զ��˳�,����Ҫִ��handler����
	//����Ҫ�����������
	pthread_cleanup_pop(0);
}


int main()
{
	pthread_mutex_init(&m,NULL);

	//�����߳�
	pthread_t tid1;
	pthread_create(&tid1,NULL,func1,NULL);
	
	pthread_t tid2;
	pthread_create(&tid2,NULL,func2,NULL);
	
	sleep(3);
	pthread_cancel(tid1);//���߳�2����ȡ���ź�
	
	pthread_exit(NULL);
}

