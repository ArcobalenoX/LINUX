/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>

/*******TCP/UDP/IP header**************/
#define  _PG_IP
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

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

#include <signal.h>

/*********Packgage function myheader****/
#include "Package.h"

/********* 链表头文件 ******************/
#include "mylist.h"


//全局变量
int 		socket_fd;//服务器到套接字 文件描述符
PNode		     head; //客户端链表头指针
fd_set 		  readfds; //多路复用
int 		   fd_max; //多路复用最大文件描述值
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int file_num = 2;
char *file_path[10] = {"./file/1.txt","./file/2.txt"};


//函数声明
void handler(int sig);
void * routine(void * arg);
int select_get(void);
void file_send(int client_fd);
void file_recv(int client_fd);
void chat_fun(int client_fd);
int file_refresh(char* dir);


int main(int argc,char **argv)
{

    if(argc != 2)
    {
        fprintf(stderr, "%s  <local port>\n",argv[0]);
        exit(-1);
    }

    signal(2, handler);
    char buf[100];
    file_refresh("./file");

    //1. 建立 socket
    socket_fd = Socket(AF_INET, SOCK_STREAM, 0);

    //2. 绑定 IP  port
    struct sockaddr_in addr_set;

    addr_set.sin_family = AF_INET;
    addr_set.sin_port = htons(atoi(argv[1]));
    addr_set.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(socket_fd, (struct sockaddr *)&addr_set, sizeof(addr_set));

    //3. 设置监听
    Listen(socket_fd, 5);

    //4. 初始化
    head =list_init();
    FD_ZERO(&readfds);
    fd_max =0;

    //5. 循环等待连接
    struct sockaddr_in client_addr;
    socklen_t size = sizeof(client_addr);


    pthread_t tid;
    pthread_create(&tid,NULL,routine,NULL);



    while(1)
    {
        /*等待客户端连接*/
        puts("waiting for connect... ...");
        int client_fd = Accept(socket_fd, (struct sockaddr*)&client_addr, &size);
        printf("client: %s  %hu\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        //把客户端信息 加入链表
        PNode tmp = Calloc(1, sizeof(Node));
        memset(buf,0,100);
        Recv(client_fd, buf,100, 0);
        strncpy(tmp->name,buf,strlen(buf));
        tmp->fd = client_fd;
        tmp->port = client_addr.sin_port;
        tmp->addr.s_addr = client_addr.sin_addr.s_addr;

        pthread_mutex_lock(&mutex);

        list_add(head, tmp);
        list_pri(head);
        //设置多路复用
        fd_max = fd_max > client_fd ? fd_max : client_fd;


        pthread_mutex_unlock(&mutex);

    }

    return 0;
}

void * routine(void * arg)
{

    PNode p;
    int fdSet;
    char buf[100];
    while(1)
    {

        if(fd_max==0)
        {
            usleep(1000*20);
            continue;
        }
        //puts("\n\n\n \t\t\t进入一级界面\n");


        while(fdSet = select_get(), !fdSet);



        chat_fun(fdSet);
    }
}

int select_get(void)
{
    int fd_use ;//fd_max+1
    int ret;//监听到的客户端
    PNode tmp;


    //1. 清空 多路复用集合
    FD_ZERO(&readfds);
    //2. 初始化 多路复用集合 + 获取最大文件描述符值 --》 并加锁保护
    pthread_mutex_lock(&mutex);

    for(tmp=head->next; tmp!=head; tmp=tmp->next)
        FD_SET(tmp->fd,&readfds);
    fd_use =fd_max+1;

    pthread_mutex_unlock(&mutex);


    //3. 多路复用等待 可读客户端
    struct timeval tm_out = {0,1000*20};//设置延时复用 20ms

    ret = select(fd_use, &readfds, NULL, NULL, &tm_out);
    if(ret == -1)	//fail
    {
        printf("select err\n");
        return -1;
    }
    else if(ret == 0)   //timeout -->no mesg
    {
        return 0;
    }
    //4.判断 哪一路 客户可读并做响应处理
    int fdSet; //保存正在通信的客户端的套接字描述符
    for(tmp=head->next; tmp!=head; tmp = tmp->next)
    {
        if( FD_ISSET(tmp->fd, &readfds) )
        {

            fdSet = tmp->fd;

            break;

        }
    }

    return fdSet;//返回监听到的可读端

}

void chat_fun(int client_fd)//客户端通信
{
    char buf[100];
    int con_fd ;
    memset(buf,0, 100);
    Recv(client_fd, buf, 100, 0);
    puts(buf);


    //获取列表 --》 接受确认 通信的另一个客户端 --》 msg + file（互传） + exit
    if(!strncmp(buf, "list", 4))
    {
        usleep(100*1000);
        //发送客户端链表
        puts("正在回应链表请求");
        Send(client_fd, &head->fd, 4, 0); //发送客户链表成员数量

        PNode tmp;
        for(tmp = head->next; tmp != head; tmp = tmp->next)
        {
            Send(client_fd, tmp, sizeof(Node), 0 );
        }

        //接收 需要通信的客户端的信息
        tmp  = (PNode)Calloc(1, sizeof(Node));
        Recv(client_fd, tmp, sizeof(Node),0);

        con_fd = list_fd_seek(head, tmp);
        free(tmp);

        if(con_fd == -1 )  //没找到
        {

            Send(client_fd, "fail", 4, 0 );
            printf("%s\tnot find",tmp->name);
        }
        else
        {
            printf("%s\tfind",tmp->name);
            Send(client_fd, "ok", 2, 0 );
            printf("进入客户端通信模式\n");
            send(con_fd,"\t\t进入聊天模式\n",100,0);
            while(1)  //二级界面--》 聊天 + 文件收发
            {
                //进入之前应该确定和 链表中的哪个客户进行通信
                int fd_set=select_get();

                memset(buf,0, 100);
                if(fd_set == client_fd)  //主动发起方
                {

                    Recv(client_fd, buf, 100, 0);
                    puts(buf);

                    if(!strncmp(buf, "msg:", 4))
                    {

                        Send(con_fd, buf, strlen(buf), 0 );

                    }


                    if(!strncmp(buf, "exit", 4))
                    {

                        memset(buf,0, 100);
                        break;

                    }

                }
                else if(fd_set == con_fd)   //被动连接方
                {

                    Recv(con_fd, buf, 100, 0);
                    puts(buf);

                    if(!strncmp(buf, "msg:", 4))
                    {

                        Send(client_fd, buf, strlen(buf), 0 );

                    }


                    else if(!strncmp(buf, "exit", 4))
                    {
                        printf("退出客户端通信模式\n");
                        memset(buf,0, 100);
                        break;

                    }

                }
            }

        }
    }
    else if(!strncmp(buf, "file", 4))  //服务器下发文件到客户端
    {

        usleep(100*1000);
        file_send(client_fd);


    }
    else if(!strncmp(buf, "upfile", 6))   //接收客户端上传文件
    {
        usleep(100*1000);
        file_recv(client_fd);




    }
    else if(!strncmp(buf, "exit", 4))   //接收客户端退出
    {
        list_del(head,client_fd);
        printf("client exit\n");

    }

}
/**
	协议：传送文件个数 ---》 循环传送文件的名字 ---》 获取需要传输的文件编号
		---》发送文件的大小 ---》 发送文件的内容
**/
void file_send(int client_fd)  //发送文件 到 客户端
{

    //传送文件个数
    Send(client_fd, &file_num, 4, 0);
    printf("send file_num: %d\n",file_num);

    //循环传送文件的名字
    int i;
    for(i=0; i< file_num; i++)
    {

        Send(client_fd, file_path[i], strlen(file_path[i]), 0);
        usleep(20*1000);
    }

    //获取需要传输的文件编号
    Recv(client_fd, &i, 4, 0);
    printf("will send file_num: %d\n",i);

    //发送文件的大小
    int fd_file = Open(file_path[i-1], O_RDONLY);

    struct stat file_info;
    fstat(fd_file, &file_info);
    Send(client_fd, &file_info.st_size, sizeof(off_t), 0);
    printf(" send file_size: %ld\n",file_info.st_size);

    //发送文件内容
    //说明：tcp 不限每次发送的最大字节数，网络层 自动分隔发送内容，分隔的大小不一致
    //udp 限制发送最大字节数 大约为 5k左右

    char * buf = (char *)Calloc(1, file_info.st_size);

    Read(fd_file, buf, file_info.st_size);

    Send(client_fd, buf, file_info.st_size, 0);

    //回收资源
    free(buf);

}
void file_recv(int client_fd)  //从客户端接收文件
{


    char buf[100];
    memset(buf, 0, 100);
    char file_name[100];
    memset(file_name,0,100);

    //接收文件的大小
    off_t file_size;
    Recv(client_fd, &file_size, sizeof(off_t), 0);
    printf("file_size: %lu\n", file_size);

    //接收文件名字
    Recv(client_fd, &buf, sizeof(buf), 0);
    printf("recv file_name: %s\n", buf);
    sprintf(file_name,"%s%s","./file/",buf);

    //保存文件名到文件数组
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        if (file_path[i] <= 0)
        {
            strcpy(file_path[i],file_name);
            break;
        }
    }


    //接收文件的内容
    int fd_file;

    fd_file = Open(file_name, O_CREAT|O_WRONLY, 0666);


    int RecvSize = 0;
    for(; RecvSize < file_size;)
    {

        memset(buf, 0, 100);

        int ret = Recv(client_fd, buf, 100, 0);
        RecvSize += ret;

        Write(fd_file, buf, ret);
    }



    //回收资源
    Close(fd_file);

}
int file_refresh(char* dir)
{
    DIR *dp;
    dp = opendir(dir);
    struct dirent *dirp;
    int i = 0;
    char filename[500]={""};
    while ((dirp =readdir(dp))!=NULL)
    {
        if(dirp->d_type == DT_REG)
        {
            printf("%s\n",dirp->d_name);
           
               
/*
                    sprintf(filename,"%s%s","./file/",dirp->d_name);
                    strncpy(file_path[i],filename,50);
                    printf("%s\n",dirp->d_name);

	i++;
                
      */      
        }
    }
	closedir(dp);
    return 0;
}

//ctrl + c --> 处理函数
void handler(int sig)
{

    close(socket_fd);
    list_free(head);
    exit(0);
}
