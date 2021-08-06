/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
#include<sys/mman.h>
#include <errno.h>
#include <stdarg.h>

/**********IO header*************/
#define  _PG_IO
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

/**********pthread header*************/
#define  _PG_thread
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

/*********Packgage function myheader****/
#include "Package.h"
#include "thread_pool.h"


thread_pool *pool;//全局线程池

void *task(void *arg);
void fcopy(char* source_path,char* destination_path);
void dir_copy(char * dir_src,char* dir_dest,int ceng);


void *task(void *arg)//线程任务
{


    /*    char *cmd = (char *)arg;

        system(cmd);

        free(cmd);
    */

    char (*tmp)[300]= (char(*)[300])arg;
    fcopy(tmp[0],tmp[1]);


}

void fcopy(char* source_path,char* destination_path)//文件复制
{
    char buf[1024];
    bzero(buf,1024);

    FILE *src,*dest;
    src=Fopen(source_path,"r");
    dest=Fopen(destination_path,"w+");

    fseek(src,0,SEEK_END);
    int total_num = ftell(src);  //文件位置指针当前位置相对于文件首的偏移字节数。
    rewind(src);//指向文件开头
    while(total_num > 0)
    {
        if(total_num >= 1024)
        {
            fread(buf,1,1024,src);
            fwrite(buf,1,1024,dest);
            total_num -=1024;
        }
        else
        {
            fread(buf,1,total_num,src);
            fwrite(buf,1,total_num,dest);
            total_num =0;
        }
    }

    Fclose(src);
    Fclose(dest);
}

void dir_copy(char * dir_src,char* dir_dest,int ceng)//目录复制
{

    DIR * dirp = Opendir(dir_src);
    struct dirent * ditm;
    char src_buf[300];
    char dest_buf[300];
    char *cmd;
    while(1)
    {

        ditm = readdir(dirp);

        if(ditm == NULL)break;

        if( ( !strcmp(ditm->d_name,".") ) || ( !strcmp(ditm->d_name,"..") ) )//忽略当前路径和上级路径
            continue;

        int i;
        for(i=0; i<ceng; i++)//ceng 为递归函数传参
        {
            printf("\t");
        }
        printf("|-->%s\n",ditm->d_name);


        if(ditm->d_type == DT_DIR)
        {
            memset(src_buf,0,300);
            memset(dest_buf,0,300);

            sprintf(dest_buf,"%s/%s",dir_dest,ditm->d_name);//拼接目录
            if(access(dest_buf,F_OK)!=0)
                Mkdir(dest_buf,0777);

            sprintf(src_buf,"%s/%s",dir_src,ditm->d_name);

            dir_copy(src_buf,dest_buf,ceng+1);//递归进入目录

        }
        else if(ditm->d_type == DT_REG)
        {

            /*           cmd = Calloc(1,300);
                       sprintf(cmd,"cp %s/%s %s/%s",\
                               dir_src,ditm->d_name, dir_dest, ditm->d_name);
                       add_task(pool,task, (void *)cmd);
            */

            sprintf(dest_buf,"%s/%s",dir_dest,ditm->d_name);
            sprintf(src_buf,"%s/%s",dir_src,ditm->d_name);

            char tmp[2][300]= {0};
            memset(tmp,'\0',600);
            strncpy(tmp[0],src_buf,300);
            strncpy(tmp[1],dest_buf,300);

            add_task(pool,task, (void *)tmp);//线程添加文件复制任务
            usleep(10000);

        }

// Closedir(dirp);
    }


}

int main(int argc,char **argv)
{

    //1. check args --> ./cmd <dir_src> <dir_dest>
    if(argv[1]==NULL||argv[2]==NULL)
    {
        printf("请输入两个文件夹的路径，第一个为源文件的路径，第二个为目标文件夹的路径\n");
        exit(-1);
    }


    if(access(argv[2],F_OK)!=0)
        Mkdir(argv[2],0777);
    //线程初始化
    pool = Calloc(1,sizeof(thread_pool));
    init_pool(pool,5);
    //2.dir_copy
    dir_copy(argv[1],argv[2],0);

    destroy_pool(pool);
    free(pool);

    return 0;
}//end of te main


