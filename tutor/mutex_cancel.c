#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t m;


void handler(void *arg)
{
	printf("m over\n");
	pthread_mutex_unlock(&m);
}


//线程函数
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
	//在加锁之前,设置解锁的函数
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
	
	//如果该线程是自动退出,则不需要执行handler函数
	//但是要把设置清除掉
	pthread_cleanup_pop(0);
}


int main()
{
	pthread_mutex_init(&m,NULL);

	//创建线程
	pthread_t tid1;
	pthread_create(&tid1,NULL,func1,NULL);
	
	pthread_t tid2;
	pthread_create(&tid2,NULL,func2,NULL);
	
	sleep(3);
	pthread_cancel(tid1);//向线程2发送取消信号
	
	pthread_exit(NULL);
}

