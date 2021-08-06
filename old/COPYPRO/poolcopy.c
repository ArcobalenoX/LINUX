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

int end=1;
static int thread_number = 0;
static int run_number=0;
static int pool_number=0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

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

int dir_add_path(char *directorypath,dir_path *head)//目录路径添加链表
{
	dir_path *temp=calloc(1,sizeof(dir_path));
	strcpy(temp->directorypath,directorypath);
	
	temp->next=NULL;
	dir_path *q=head;
	while(q->next!=NULL)
		q=q->next;
	q->next=temp;
	return 0;
}
int file_add_path(char *filepath,char * filesourcepath,file_path *head)//文件路径添加链表
{

	file_path *temp=calloc(1,sizeof(file_path));
	strcpy(temp->filepath,filepath);
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
	
	char temp1[512];//源目录
	char temp2[512];//目的目录
	DIR *dir=opendir(dirsource);
	struct dirent *ent;
	
	while((ent=readdir(dir))!=NULL)
	{
		bzero(temp1,sizeof(temp1));
		bzero(temp2,sizeof(temp2));
		
		if(!strcmp(ent->d_name,".")||!strcmp(ent->d_name,".."))
			continue;
		sprintf(temp1,"%s/%s",dirsource,ent->d_name);//源目录
		sprintf(temp2,"%s/%s",dirdest,ent->d_name);//目的目录
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

void copyfile(file_path * head)
{
	file_path *q=head;
	
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
	end=0;
	printf("复制完成\n");
}




//线程任务
 void *thread_run(void *myfile_path)
{
	file_path* path=(file_path*)myfile_path;
	while(end)
	{
		pthread_mutex_lock(&mutex);
	
		if(end==0)//判断当前的任务
		{
			printf("id = %lu   run:%d  pool:%d  thread:%d\n",
				pthread_self(), run_number, pool_number, thread_number);	
			printf("当前任务为0，即将退出\n");
			pthread_mutex_unlock(&mutex);//当前任务为0，就解锁退出
			pthread_exit (NULL);
		}	
		
		printf("id = %lu   run:%d  pool:%d  thread:%d\n",
			pthread_self(), run_number, pool_number, thread_number);	
			
		pthread_cond_wait(&cond, &mutex);
		
		pthread_mutex_unlock(&mutex);
		//执行任务
		copyfile(path);
		run_number++;
		pool_number--;
	
		
		
		run_number--;
		pool_number++;

	}
	pthread_exit (NULL);
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
        printf("你输入的第一个参数或者第二个参数不是文件夹\n");
    }
	
	dir_path *mydirectory_path=initial_path();
	file_path *myfile_path=initial1_path(mydirectory_path);
	
	
	
	allpath(source_path,destination_path,mydirectory_path,myfile_path);//进行路径分类
	
	printf("需要复制的目录\n");
	display(mydirectory_path);
	
	printf("需要复制的文件\n");
	display2(myfile_path);
	
	end=1;
	dir_path *p=mydirectory_path;
	while(p->next!=NULL)
	{	 
		p=p->next;
		make_dirs(p->directorypath, 0777);//从目录的链表中创建目录
	}
	
	
	pthread_t tid = 0;
	int ret  = 0;
	for(int i=0; i<5; i++)
	{
		ret = pthread_create(&tid, NULL, thread_run, &(myfile_path));
		pthread_detach(tid);
		thread_number++;
		pool_number++;
	}
	while(end)
	{	
		pthread_mutex_lock(&mutex);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	
	pthread_cancel(tid);
	pthread_join(tid,NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	pthread_exit(NULL);
	printf("结束\n");
	return 0;
	
}









