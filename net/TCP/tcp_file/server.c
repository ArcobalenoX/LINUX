/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>

/**********IO header*************/
#define  _PG_IO
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

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

/*********Packgage function myheader****/
#include "Package.h"


void * routine(void *arg)
{
    int fd =  *(int *)arg;
    int size;
    FILE *fp;
    char buf[100];

    while(1)
    {
        memset(buf, 0, 100);
        fgets(buf,100,stdin);
        Send(fd, buf, strlen(buf), 0);
		
        if(!strncmp(buf,"file",4))//传输文件
        {

            memset(buf, 0, 100);
            puts("input file name");
            scanf("%s",buf);
            fp=fopen(buf,"r");
			
            fseek(fp,0,SEEK_END);
            size=ftell(fp);
            fseek(fp,0,SEEK_SET);
            printf("file size %d\n",size);
			Send(fd, &size, sizeof(size), 0);
			
            for(int i=0;i<size/100;i++)
            {
                memset(buf, 0, 100);
                if(fread(buf,100,1,fp)==0)
                    break;
                printf("%s",buf);
                Send(fd, buf,100, 0);
                
            }
            memset(buf, 0, 100);
            fread(buf,size%100,1,fp);

            printf("%s",buf);
            Send(fd, buf, size%100, 0);

            puts("send over");
            Fclose(fp);

        }


        if(!strncmp(buf,"chat",4))
        {
            memset(buf, 0, 100);
            fgets(buf,100,stdin);
            Send(fd, buf, strlen(buf), 0);
        }

        if(!strncmp(buf,"exit",4))
        {
            break;
        }
    }


}



int main(int argc,char **argv)
{


    int server_port = 50000;


    //1. 创建套接字
    int socket_fd = Socket(AF_INET, SOCK_STREAM, 0);

    //2. 绑定
    struct sockaddr_in tcp_addr;

    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(server_port);
    tcp_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(socket_fd, (struct sockaddr *)&tcp_addr, sizeof(tcp_addr));

    //3. 设置监听
    Listen(socket_fd, 5);

    //4. 等待连接
    struct sockaddr_in client_addr;
    unsigned int size = sizeof(client_addr);

    puts("waiting for accept... ...");
    int client_fd = Accept(socket_fd, (struct sockaddr *)&client_addr, &size);

    printf("client : port:%u , addr:%s\n\n",\
           ntohs(client_addr.sin_port), inet_ntoa(client_addr.sin_addr));

    //5. 创建线程 对客户端进行写入
    pthread_t tid;
    Pthread_create(&tid, NULL, routine, (void *)&client_fd );


    while(1)
    {


    }


    // 回收资源
    pthread_join(tid, NULL);
    Close(socket_fd);

    return 0;
}//end of te main


