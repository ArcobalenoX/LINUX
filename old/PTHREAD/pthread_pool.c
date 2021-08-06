#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


static int thread_number = 0;
static int run_number=0;
static int pool_number=0;


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


//任务链表




void task_run()
{
	printf("task-----\n");
	sleep(5);
}


void *thread_run(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		pthread_cond_wait(&cond, &mutex);
		pthread_mutex_unlock(&mutex);
		
		run_number++;
		pool_number--;

		printf("id = %lu   run:%d  pool:%d  thread:%d\n",
			pthread_self(), run_number, pool_number, thread_number);
		sleep(5);
		//执行任务

		run_number--;
		pool_number++;

	}
}

int main(void)
{
	pthread_t id = 0;
	
	int ret  = 0;
	int i=0;
	
	for(i=0; i<5; i++)
	{
		ret = pthread_create(&id, NULL, thread_run, NULL);
		pthread_detach(id);
		thread_number++;
		pool_number++;
	}

	while(1)
	{
		//添加任务	
		getchar();
		if(pool_number > 0)
		{
			pthread_mutex_lock(&mutex);
			pthread_cond_signal(&cond);
			pthread_mutex_unlock(&mutex);
		}
		else
		{
			ret = pthread_create(&id, NULL, thread_run, NULL);
			pthread_detach(id);
			thread_number++;
			pool_number++;
			//printf("pool NULL\n");
		}
	}
	return 0;
}
