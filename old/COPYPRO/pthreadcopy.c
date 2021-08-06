#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

typedef struct path //目录路径
{
	char directorypath[50];//存放目录路径
	struct path *next;
	
}dir_path;

typedef struct path1//文件路径
{
	char filepath[50];//目标路径
	char filesourcepath[50];//源文件路径
	struct path1 *next;
	
}file_path;

typedef struct taskplate//任务单链表
{
	void*(*q)(void *parameter);
	void* parameter;
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

//线程池添加任务
int add_task(pool* myhead,void *(*ts)(void *arg),void *arg)//尾插任务节点
{
	
	ptask new_threadpool=calloc(1,sizeof(task));//初始化一个任务节点
	new_threadpool->q=ts;//传进来的函数
	new_threadpool->parameter = arg;//传给函数的参数
	
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
		
        pthread_create(&((mypool->id)[i]),NULL,thread_task,mypool);//把初始好的mypool传给thread_task进行创建
    }
	return mypool;
}

bool pool_destroy(pool *mypool)//消毁线程
{
	pthread_cond_broadcast(&mypool->threadcond);//消毁条件变量
	
	int i=0;

	for(;i<mypool->threadnum;i++)//循环消毁mypool->threadnum个线程
	{
		pthread_join(((mypool->id)[i]),NULL);
	}
	
	/*free(mypool->id);
	free(mypool->curtask);
	free(mypool); */
	return true;
}


dir_path *initial_path()//初始化目录路径
{
	dir_path *head=calloc(1,sizeof(dir_path)); 
	head->next=NULL;
	return head;
}
file_path *initial1_path(dir_path *dir_head)//初始化文件路径
{
	file_path *head=calloc(1,sizeof(file_path)); 
	head->next=NULL;
	return head;
}

int dir_add_path(char *directorypath,dir_path *head)//目录路径
{
	dir_path *temp=calloc(1,sizeof(dir_path));
	strcpy(temp->directorypath,directorypath);//把拼接好的目录路径拷贝到目录路径的数组里
	
	temp->next=NULL;
	dir_path *q=head;
	while(q->next!=NULL)
		q=q->next;
	q->next=temp;
	//printf("目录路径%s\n",q->next->directorypath);
	return 0;
}
int file_add_path(char *filepath,char * filesourcepath,file_path *head)//文件路径
{

	file_path *temp=calloc(1,sizeof(file_path));
	strcpy(temp->filepath,filepath);//把拼接好的  目标文件路径  拷贝到文件路径的数组里
	strcpy(temp->filesourcepath,filesourcepath);
	
	temp->next=NULL;
	file_path *q=head;
	while(q->next!=NULL)
		q=q->next;
	q->next=temp;
	return 0;
}

//查找路径
int allpath(char * dirsource,char *dirdest,dir_path* mydir_path,file_path* myfile_path)
{
	
	char temp1[512];//目录路径
	char temp2[512];//文件路径
	
	DIR *dir=opendir(dirsource);
	struct dirent *ent;
	
	while((ent=readdir(dir))!=NULL)
	{
		bzero(temp1,sizeof(temp1));
		bzero(temp2,sizeof(temp2));

				//拼接当前路径和目标路径
		
		if(!strcmp(ent->d_name,".")||!strcmp(ent->d_name,".."))
			continue;
		sprintf(temp1,"%s/%s",dirsource,ent->d_name);
		sprintf(temp2,"%s/%s",dirdest,ent->d_name);
		if((ent->d_type==DT_DIR))//判断目录
		{
			dir_add_path(temp2,mydir_path);//添加目录路径节点
			allpath(temp1,temp2,mydir_path,myfile_path);//递归		
		}
		else 
		{
			
			if(ent->d_type==DT_REG)//判断文件
			{			
				file_add_path(temp2,temp1,myfile_path);//添加文件路径节点				
			}
		}
	}
	closedir(dir);

}



int make_dirs(char *dir, __mode_t m)
{
    if(NULL == dir || '\0' == *dir)
        return -1;
 
    char *p = strrchr(dir, '/');
 
    if(p != NULL)
    {
        char parent_dir[4096] = { 0 };
        strncpy(parent_dir, dir, p - dir);
        if(access(parent_dir, F_OK) != 0)
            make_dirs(parent_dir, m);
    }
 
    if(access(dir, F_OK) != 0)
    {
        if( mkdir(dir, m) != 0)
            return -1;
    }
 
    return 0;
}




//遍历打印链表数据
void display(dir_path *head)
{
	dir_path *p=head;
	while(p->next !=NULL)
	{
		p=p->next;
		printf("目录%s\n",p->directorypath);
		
	}
	
}
void display2(file_path *head)
{
	file_path *p=head;
	while(p->next !=NULL)
	{
		p=p->next;
		printf("文件%s\n",p->filepath);
		
	}
	
}
void * copyfile(void * head)
{
	file_path *q=(file_path *)head;
	
	while(q->next!=NULL)
	{	 
		q=q->next;
		
		char* source_path = q->filesourcepath;
		char* destination_path = q->filepath;
		char buffer[1024];
		int in,out,size;
		int fd,fd1;
		fd=open(source_path,O_RDWR);
		if(fd==-1)
		{
			printf("打开文件失败\n");
			exit(1);
		}
		out=read(fd,buffer,1024);
		if(out==-1)
		{
			printf("读取失败\n");
			exit(1);
		}
		close(fd);
		size=strlen(buffer);
		fd1=open(destination_path,O_WRONLY|O_CREAT,S_IRWXU|S_IRWXG);
		if(fd1==-1)
		{
			printf("打开文件失败\n");
			exit(1);
		}
		in=write(fd1,buffer,size);
		if(in==-1)
		{
			printf("写入失败\n");
			exit(1);
		}
	}
}


 
int main(int argc,char *argv[])
{
	  if(argv[1]==NULL||argv[2]==NULL)
    {
        printf("请输入两个文件夹的路径，第一个为源文件的路径，第二个为目标文件夹的路径\n");
        exit(1);
    }
    char* source_path=argv[1];
    char* destination_path=argv[2];
    DIR* source=opendir(source_path);
    DIR* destination=opendir(destination_path);
    if(!source||!destination)
    {
        printf("你输入的第一个参数或者第二个参数不是文件夹或不存在\n");
    }
	
	dir_path *mydirectory_path=initial_path();
	file_path *myfile_path=initial1_path(mydirectory_path);
	
	allpath(source_path,destination_path,mydirectory_path,myfile_path);//进行路径分类
	
	dir_path *p=mydirectory_path;
	while(p->next!=NULL)
	{	 
		p=p->next;
		//printf("%s\n",p->directorypath);
		make_dirs(p->directorypath, 0777);//从目录的链表中创建目录
	}
	
	//copyfile(myfile_path);
	
	printf("需要复制的目录\n");
	display(mydirectory_path);
	
	printf("需要复制的文件\n");
	display2(myfile_path);
	
	
	printf("开始复制\n"); 
	sleep(2);
	
	pool *mypool=threadpool_init(6);//创建6个线程的把线程池的头节点赋给mypool
	//添加任务
		add_task(mypool,copyfile,myfile_path);//投放任务
	sleep(2);
	//销毁线程
	pool_destroy(mypool); 
	printf("结束\n"); 
	return 0;
	
}









