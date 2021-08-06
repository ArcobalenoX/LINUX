/**
*
*	@File Name:main.c
*	@Author:岳秀超 17691051169
*	@Version:1.0
*	@Brief:多线程主函数
*	@Date:2019.6.3
*
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#include"slist.h"
#include"http.h"


#define MAX_URL_LEN 200
#define MAX_PATH_LEN 100
#define MAX_TASK_CNT 10

typedef struct
{
    char url[MAX_URL_LEN];
    char save_path[MAX_PATH_LEN];
} DOWNLOAD_TASK;


typedef enum
{
    PRIO_NORMAL,
    PRIO_HIGH

} DOWNLOAD_PRIO;

typedef struct
{
    long msg_type;
    char url[MAX_URL_LEN];
    char save_path[MAX_PATH_LEN];


} MSG_ST;


int task_add(char *url,char * save_path,DOWNLOAD_PRIO prio);
int task_add_bymsg(char *url,char * save_path);
void*download_thread_msg(void*arg);
int init_service();
int deinit_service();
int init_msg();
int deinit_msg();
void * callback(void*arg);





pthread_t tid=0;
static Z_SLIST task_slist=NULL;
static int msg_id=1;

int task_add(char *url,char * save_path,DOWNLOAD_PRIO prio)
{
    int ret=-1;
    DOWNLOAD_TASK task= {0};
    strncpy(task.url,url,sizeof(task.url));
    strncpy(task.save_path,save_path,sizeof(task.save_path));
    if(prio==PRIO_HIGH)
    {
        ret=task_slist_insert(task_slist,&task,0);
    }
    else
    {
        ret=task_slist_add(task_slist,&task);
    }
    return ret;

}

int task_add_bymsg(char *url,char * save_path)
{
    MSG_ST msg= {0};
    msg.msg_type=1;
    strncpy(msg.url,url,sizeof(msg.url));
    strncpy(msg.save_path,save_path,sizeof(msg.save_path));
    msgsnd(msg_id,(void*)&msg,MAX_URL_LEN+MAX_PATH_LEN,0);


    return 0;

}



void*download_thread_msg(void*arg)
{
	
    DOWNLOAD_TASK * task=NULL;
    MSG_ST msg= {0};
    while(1)
    {
        if(msgrcv(msg_id,(void*)&msg,MAX_URL_LEN+MAX_PATH_LEN,1,0)>0)
        {
            printf("msgrcv:url=%s:,path=%s\n",msg.url,msg.save_path);
            DOWNLOAD_TASK new_task= {0};
            strncpy(new_task.url,msg.url,sizeof(new_task.url));
            strncpy(new_task.save_path,msg.save_path,sizeof(new_task.save_path));
            task_slist_add(task_slist,&new_task);

        }
        task=(DOWNLOAD_TASK*)task_slist_get(task_slist,0);
        if(task!=NULL)
        {
            printf("New download task:\n");
            printf("Downloading...url=%s:\n",task->url);

			http_download(task->url, task->save_path);
            sleep(5);
            callback(task);
			
			
            task_slist_delete(task_slist,0);

        }
        sleep(1);
    }
    return NULL;

}


int init_service()
{
    task_slist=task_slist_new(sizeof(DOWNLOAD_TASK),MAX_TASK_CNT);
    pthread_create(&tid,NULL,download_thread_msg,NULL);
    return tid;
}


int deinit_service()
{
    int ret=-1;
    ret =pthread_cancel(tid);
    if(0==ret)
    {
        pthread_join(tid,NULL);
    }
    return ret;


}
int init_msg()
{
    msg_id=msgget((key_t)1234,IPC_CREAT|0666);
    return msg_id;
}

int deinit_msg()
{

    return msgctl(msg_id,IPC_RMID,0);

}

void * callback(void*arg)
{
	DOWNLOAD_TASK* task=(DOWNLOAD_TASK*)arg; 
	printf("Downloading...url=%s:\n",task->url);
	printf("Finish save_path=%s\n",task->save_path);
	/*FILE *fp=fopen(task->save_path,"r");
	long size =ftell(fp);
	printf("%s size is %ld\n",task->save_path,size);
	fclose(fp);*/
}

int main()
{
    init_service();
    init_msg();

    task_add_bymsg("http://39.108.177.3:8080/images/bill.jpg","./bill.jpg");
	
	sleep(10);
 
    deinit_msg();
    deinit_service();

    return 0;
}