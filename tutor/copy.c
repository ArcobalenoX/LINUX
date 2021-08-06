#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

typedef struct taskplate//任务单链表
{
	void*(*q)(void *parameter);
	void *parameter;
	struct taskplate *next;
}task,* ptask;
typedef struct threadpool//线程池
{
	int threadnum;//表示线程池中总的线程数量;
	pthread_t *id;//存放线程池中所有线程的id
	bool threadflag;//表示线程池是生是死
	struct taskplate *curtask;//指向任务链表中你要处理任务
	pthread_mutex_t threadmutex;//协调线程池取任务和主函数添加任务
	pthread_cond_t threadcond;//当任务数量为0，阻塞当前线程池中所有的线程，等到有任务了再唤醒线程池中的线程
	int tasknum;//统计当前任务链表中任务的数量
}pool;
typedef struct path //目录路径
{
	char directorypath[50];//存放目录路径
	struct path *next;
	
}all_path;

typedef struct path1//文件路径
{
	char filepath[50];//目标路径
	char targetfilepath[50];//原文件路径
	struct path *dir_next;//嵌套目录路径
	
	struct path1 *next;
	
}all_path1;
//线程池添加任务
int add_task(pool* myhead,void *(*ts)(void *arg),void *arg)//尾插任务节点
{
	
	ptask new_threadpool=calloc(1,sizeof(task));//初始化一个任务节点
	new_threadpool->q=ts;//传进来的函数
	new_threadpool->parameter=arg;//传给函数的参数
	new_threadpool->next=NULL;//任务节点的下一个节点指向NULL
	
	ptask p=myhead->curtask;//取出任务链表中你要处理任务
	
	pthread_mutex_lock(&myhead->threadmutex);//上锁
	while(p->next!=NULL)//遍历
		p=p->next;
	
	p->next=new_threadpool;//把新的节点放在任务链表中你要处理任务节点的下一个
	myhead->tasknum++;//当前任务链表中任务的数量++
	pthread_mutex_unlock(&myhead->threadmutex);//解锁
	
	pthread_cond_signal(&(myhead->threadcond));//随机唤醒一个线程执行任务
	return 0;
}

//线程执行1个拷贝任务,然后退出
void *thread_task(void *arg)//取出任务
{
    pool *temp=(pool *)arg;//传进来的线程池强转类型
	
    pthread_mutex_lock(&temp->threadmutex);//上锁
    if(temp->tasknum==0)//判断当前的任务
    {
		printf("当前任务为0，即将退出\n");
		pthread_mutex_unlock(&temp->threadmutex);//当前任务为0，就解锁退出
		pthread_exit (NULL);
    }
     //取出任务（本质就是删除头结点后面的节点）
	ptask other=temp->curtask->next;//取出任务
	temp->curtask->next=other->next;//把取出的任务删除，也就是把线程池任务链表的指向下下一个
    temp->tasknum--;//当前链表中任务的数量--
    pthread_mutex_unlock(&temp->threadmutex);//解锁
	
    //处理任务
    (other->q)(other->parameter); //通过函数指针调用指向的函数
	
	free(other);//释放任务
	pthread_exit (NULL);//退出线程
}


pool *threadpool_init(int num)//初始化线程池
{
	pool *mypool=calloc(1,sizeof(pool));//给一个线程池分配空间
	mypool->threadnum=num;//线程的总个数
	mypool->id=calloc(1,sizeof(num)*4);//给线程ID分配空间
    mypool->threadflag=true;//当前的线程池的生死
    mypool->curtask=calloc(1,sizeof(task));//给指向任务节点分配空间
    mypool->tasknum=0;//初始化任务链表中任务的数量
	pthread_mutex_init(&mypool->threadmutex,NULL);//初始化互斥锁
	pthread_cond_init(&mypool->threadcond,NULL);//初始化条件
	int i;
	for(i=0; i<num; i++)//创建num个线程
    {
						//循环线程的ID
        pthread_create(&((mypool->id)[i]),NULL,thread_task,mypool);//把初始好的mypool传给thread_task进行创建
    }
	return mypool;//返回初始化好的线程池
}

bool pool_destroy(pool *mypool)//消毁线程
{
	pthread_cond_broadcast(&mypool->threadcond);//消毁条件变量
	
	int i=0;

	for(;i<mypool->threadnum;i++)//循环消毁mypool->threadnum个线程
	{
		pthread_join(((mypool->id)[i]),NULL);
	}
	
	//free(mypool->id);
	//free(mypool->curtask);
	//free(mypool); 
	return true;
}


all_path *initial_path()//初始化目录路径
{
	all_path *head=calloc(1,sizeof(all_path)); 
	head->next=NULL;
	return head;
}
all_path1 *initial1_path(all_path *dir_hade)//初始化文件路径
{
	all_path1 *head=calloc(1,sizeof(all_path1)); 
	head->dir_next=dir_hade;//在文件路径中的结构体嵌套目录路径初始化指向目录路径的头节点
	head->next=NULL;
	return head;
}

int dir_add_path(char *directorypath,all_path *head)//目录路径
{
	all_path *temp=calloc(1,sizeof(all_path));
	strcpy(temp->directorypath,directorypath);//把拼接好的目录路径拷贝到目录路径的数组里
	
	temp->next=NULL;

	all_path *q=head;
	while(q->next!=NULL)
		q=q->next;
	q->next=temp;
	printf("目录路径%s\n",q->next->directorypath);
	return 0;
}
int file_add_path(char *filepath,char *targetfilepath,all_path1 *head)//文件路径
{

	all_path1 *temp=calloc(1,sizeof(all_path1));
	strcpy(temp->filepath,filepath);//把拼接好的  目标文件路径  拷贝到文件路径的数组里
	strcpy(temp->targetfilepath,targetfilepath);//把拼接好的  原文件路径  拷贝到文件路径的数组里
	temp->next=NULL;
	
	
	all_path1 *q=head;
	while(q->next!=NULL)
		q=q->next;
	q->next=temp;
	printf("目标文件路径%s\n",q->next->filepath);
	return 0;
}

//查找路径
int allpath(char * targetpath,char *cp_path,all_path* mydir_path,all_path1* myfile_path)//寻找路径
{
	//用来拼接目录路径
	char temp1[300];
	char temp2[300];//存放当前 文件路径
	
	DIR *dir=opendir(targetpath);
	struct dirent *ent;
	
	while((ent=readdir(dir))!=NULL)
	{
		bzero(temp1,sizeof(temp1));
		bzero(temp2,sizeof(temp2));

		
		if(!strcmp(ent->d_name,".")||!strcmp(ent->d_name,".."))
			continue;
		if((ent->d_type==DT_DIR))//判断目录
		{
		
			sprintf(temp2,"%s/%s",targetpath,ent->d_name);//拼接当前路径
			sprintf(temp1,"%s%s",cp_path,temp2);//拼接当前路径和目标路径
			dir_add_path(temp1,mydir_path);//添加目录路径的节点
			allpath(temp2,cp_path,mydir_path,myfile_path);//递归
		}
		else 
		{
			if(ent->d_type==DT_REG)//判断文件
			{
				sprintf(temp2,"%s/%s",targetpath,ent->d_name);//拼接当前路径
				sprintf(temp1,"%s%s",cp_path,temp2);//拼接当前路径和目标路径
				//printf("%s\n",temp1);
	
				file_add_path(temp1,temp2,myfile_path);//添加 目标路径 和 原文件路径 的节点
				
			}
		}
	}
	closedir(dir);

}

 void *filepath_cp(void *arg)//文件拷贝
{
	all_path1 *temp=(all_path1 *)arg;
	all_path1 *q=temp;
	FILE * fd;//原文件文件符
	FILE * fd1;//目标文件文件符
	char buf[1];//拷贝数组
	int ret;
	while(q->next!=NULL)
	{
		ret=0;
		bzero(buf,sizeof(buf));
		q=q->next;
		printf("原文件路径%s\n",q->targetfilepath);
		fd=fopen(q->targetfilepath,"r+");//打开原文件
		fd1=fopen(q->filepath,"w+");//打开目标
		while(1)
		{
			//拷贝
			ret=fread(buf,1,1,fd);
			if(ret==0)
				break;
			fwrite(buf,1,1,fd1);
		}
		//关闭
		fclose(fd);
		fclose(fd1);
	}    
	
}
 
int main(int argc,char **argv)
{
	printf("读取文件路径\n");
	all_path *mydirectory_path=initial_path();
	all_path1 *myfile_path=initial1_path(mydirectory_path);
	
	char temp[300];//存放目标路径
	bzero(temp,sizeof(temp));
	sprintf(temp,"%s%s",argv[2],argv[1]);//拼接目标路径
	printf("当前路径：%s\n",temp);
	mkdir(temp, 0777); //打开目标路径
	
	allpath(argv[1],argv[2],mydirectory_path,myfile_path);//进行路径分类
	sleep(1);
	all_path1 *q=myfile_path;
	all_path *p=q->dir_next;//使用嵌套目录
	while(p->next!=NULL)
	{	
		p=p->next;
		//printf("%s\n",p->directorypath);
		mkdir(p->directorypath, 0777);//从目录的链表中创建目录
	}    

	sleep(2);
	pool *mypool=threadpool_init(6);//创建6个线程的把线程池的头节点赋给mypool
	//添加任务
	
	add_task(mypool,filepath_cp,myfile_path);//投放任务
	
	sleep(2);
	//销毁线程
	pool_destroy(mypool); 
	 
	return 0;
	
}









