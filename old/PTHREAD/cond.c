#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int num;
pthread_mutex_t m;
pthread_cond_t v;

void *func(void *arg)
{
	int i=*(int*)arg;
	printf("func start %d\n",i);
	
	pthread_mutex_lock(&m);//加锁
	
	//如果全局变量num小于100,则释放锁,并设置条件变量阻塞
	if(num<100)
		pthread_cond_wait(&v,&m);
	printf("func continue %d\n",i);
	sleep(1);
	printf("func %d unlock\n",i);
	pthread_mutex_unlock(&m);//解锁
		
	printf("func end %d\n",i);
	pthread_exit(NULL);
}


int main()
{
	//初始化锁和条件变量
	pthread_mutex_init(&m,NULL);
	pthread_cond_init(&v,NULL);
	
	int i=0;
	pthread_t tid[3];
	for(i=0;i<3;i++)
	{
		pthread_create(&tid[i],NULL,func,(void *)&i);
		sleep(1);
	}
	
	
	sleep(1);
	
	pthread_mutex_lock(&m);//加锁
	
	while(num<100)
	{
		num+=20;
		sleep(1);
		printf("num=%d\n",num);
	}
	
	pthread_mutex_unlock(&m);//解锁
	//pthread_cond_signal(&v);//向条件变量发送一个信号
	pthread_cond_broadcast(&v);//向所有等待状态的条件变量发送信号
	
	for(i=0;i<3;i++)
		pthread_join(tid[i],NULL);
	
	//删除锁和条件变量
	pthread_cond_destroy(&v);
	pthread_mutex_destroy(&m);
	
	pthread_exit(NULL);
}