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

/**********pthread header*************/
#define  _PG_thread
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>

/**********IO header*************/
#define  _PG_IO
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

#include<signal.h>

/*********Packgage function myheader****/
#include "Package.h"


#include "mylist.h"

int socket_fd;
PNode head ;

void file_recv(int socket_fd);
void file_send(int socket_fd);

//客户端 接收 线程
void * routine(void *arg)
{

    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);//线程立即取消

    int fd = *(int *)arg;
    char buf[100];
    int ret;
    while(1)
    {
        memset(buf,0,100);
        ret = Recv(fd, buf, 100, 0);

        puts(buf);

        if(!strncmp(buf, "msg:", 4))
        {

            printf("%s from other client ",buf);
        }
		 if(!strncmp(buf, "file", 4))
        {
			file_recv(fd);
            printf("%s from other client ",buf);
        }
		


    }
}
//ctrl + c --> 处理函数
void handler(int sig)
{
    Send(socket_fd,"exit", 10, 0);
    close(socket_fd);
    list_free(head);
    exit(0);
}




int main(int argc,char **argv)
{

    if(argc != 4)
    {
        fprintf(stderr, "%s  <local port>  <server_ip>  <server port>\n",argv[0]);
        exit(-1);
    }
    char buf[100];

    signal(2, handler);

    //1. 建立 socket
    socket_fd = Socket(AF_INET, SOCK_STREAM, 0);

    //2. 绑定 IP  port
    struct sockaddr_in addr_set;

    addr_set.sin_family = AF_INET;
    addr_set.sin_port = htons(atoi(argv[1]));
    addr_set.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(socket_fd, (struct sockaddr *)&addr_set, sizeof(addr_set));


    //3. 连接服务器
    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[2]);
    server_addr.sin_port = htons(atoi(argv[3]));

    socklen_t size = sizeof(server_addr);
    Connect(socket_fd, (struct sockaddr*)&server_addr, size);


    puts("connect server success\tinput your name");
    scanf("%s",buf);
    Send(socket_fd, buf, strlen(buf), 0);


    //4. 创建 接收 线程
    pthread_t tid;

    pthread_create(&tid, NULL, routine, (void *)&socket_fd);


    //5. 和服务器 通信

    head = list_init();
    while(1)
    {
        puts("\t\t\t输入 list 获取客户端列表");
        puts("\t\t\t输入 file 获取文件列表");
        puts("\t\t\t输入 upfile 上传文件到服务器");
        puts("\t\t\t输入 exit 退出程序");

        memset(buf, 0, 100);
        scanf("%s", buf);
        Send(socket_fd, buf, strlen(buf), 0);

        if(!strncmp(buf, "list", 4))
        {

            //关闭接收线程 读端
            pthread_cancel(tid);
            usleep(100*1000);


            //链表初始化
            list_free(head);
            head = list_init();
            int n;
            Recv(socket_fd, &n, 4,0);
            while(n--)
            {

                PNode tmp = (PNode)Calloc(1, sizeof(Node));

                Recv(socket_fd, tmp, sizeof(Node),0);

                list_add(head, tmp);
            }
            list_pri(head);



            //发送需要通信的客户端信息
            Node q;
            /*

			puts("请输入需要通信的客户端 IP");
			memset(buf, 0, 100);
			scanf("%s",buf);
			puts("请输入需要通信的客户端 端口号");
			scanf("%hu",&q.port);
			q.port = ntohs(port);
			q.addr.s_addr = inet_addr(buf);
            */
            puts("请输入需要通信的客户端");
            memset(buf, 0, 100);
            scanf("%s",buf);
            strcpy(q.name,buf);
            Send(socket_fd, &q, sizeof(Node), 0);



            //确认服务器回应，是否与其他客户建立连接
            memset(buf, 0, 100);
            Recv(socket_fd, buf, 100,0);

            //恢复线程接收函数
            pthread_create(&tid, NULL, routine, (void *)&socket_fd);


            if(!strncmp(buf, "fail",4))
            {
                printf("%s not find\n",q.name);

            }
            else if(!strncmp(buf, "ok",2))
            {

                puts("\t\t\t进入聊天模式\n");
                puts("\t\t\t输入 msg: 发送消息");
                puts("\t\t\t输入 file 下载文件");

                puts("\t\t\t输入 exit 退出聊天模式");
                while(1)
                {
                    //发送消息到服务器
                    memset(buf, 0, 100);
                    scanf("%s", buf);
                    Send(socket_fd, buf, strlen(buf), 0);

                    if(!strncmp(buf, "exit", 4))
                    {
                        printf("退出聊天模式\n");
                        memset(buf, 0, 100);
                        break;

                    }
                    if(!strncmp(buf, "file", 4))
                    {
                        printf("进入文件模式\n");
						file_send(socket_fd);
                        memset(buf, 0, 100);

                    }

                }
            }
            else
            {
                puts("confirm fail");
            }


        }

        else if(!strncmp(buf, "file", 4)) //从服务器下载文件
        {
            pthread_cancel(tid);
            usleep(100*1000);


            file_recv(socket_fd);
            printf("recv file over\n");

            pthread_create(&tid,NULL,routine,(void *)&socket_fd);

        }
        else if(!strncmp(buf, "upfile", 6))   //上传文件到服务器
        {
            usleep(100*1000);
            file_send(socket_fd);


        }


        else if(!strncmp(buf, "exit", 4))
        {

            break;
        }
    }


    pthread_cancel(tid);
    close(socket_fd);

    return 0;
}//end of te main
/**
	协议：接收文件个数 ---》 循环接收文件的名字 ---》 发送需要下载的文件编号
		---》接收文件的大小 ---》 接收文件的内容
**/
void file_recv(int socket_fd)  //从服务器下载文件
{


    //接收文件个数
    int file_num;

    Recv(socket_fd, &file_num, 4,0);
    printf("recv file_num: %d\n",file_num);

    //循环接收文件的名字
    int i;

    char buf[100];
    printf("\t\t\t文件列表\n");
    for(i=0; i< file_num; i++)
    {

        memset(buf, 0, 100);

        Recv(socket_fd, buf, 100, 0);
        usleep(20*1000);

        printf("\t\t%d. %s\n",i+1, buf);

    }

    //发送需要下载的文件编号
    puts("请输入需要下载的文件编号：");
    scanf("%d",&i);

    Send(socket_fd, &i, 4, 0);

    //接收文件的大小
    off_t file_size;
    Recv(socket_fd, &file_size, sizeof(off_t), 0);
    printf("file_size: %lu\n", file_size);


    //接收文件的内容
    int fd_file;

    fd_file = Open("rcv.file", O_CREAT|O_WRONLY, 0666);


    int RecvSize = 0;
    for(; RecvSize < file_size;)
    {

        memset(buf, 0, 100);

        int ret = Recv(socket_fd, buf, 100, 0);
        RecvSize += ret;

        Write(fd_file, buf, ret);
    }



    //回收资源
    Close(fd_file);

}

void file_send(int socket_fd)  //发送文件 到 服务器
{

    char file_path[50];

    printf("which file will send  ?\n");

    scanf("%s",file_path);
    //发送文件的大小
    int fd_file = Open(file_path, O_RDONLY);

    struct stat file_info;
    fstat(fd_file, &file_info);
    Send(socket_fd, &file_info.st_size, sizeof(off_t), 0);
    printf(" send file_size: %ld\n",file_info.st_size);

    //发送文件名字
    Send(socket_fd, file_path, sizeof(file_path), 0);

    //发送文件内容
    //说明：tcp 不限每次发送的最大字节数，网络层 自动分隔发送内容，分隔的大小不一致
    //udp 限制发送最大字节数 大约为 5k左右

    char * buf = (char *)Calloc(1, file_info.st_size);

    Read(fd_file, buf, file_info.st_size);

    Send(socket_fd, buf, file_info.st_size, 0);

    //回收资源
    free(buf);

}
