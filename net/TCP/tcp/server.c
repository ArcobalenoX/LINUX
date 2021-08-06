/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
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


    char buf[100];
    while(1)
    {
        memset(buf, 0, 100);
        fgets(buf,100,stdin);

        Send(fd, buf, strlen(buf), 0);

        if(!strncmp(buf,"exit",4))
        {
            break;
        }
    }


}



int main(int argc,char **argv)
{

    //0. 判断参数合法性
    if(argc != 2)
    {
        fprintf(stderr, "usage:%s <server_PORT> \n",argv[0]);
        exit(-1);
    }

    int server_port = atoi(argv[1]);
    if(server_port < 50000)
    {
        fprintf(stderr, "prot >= 50000\n");
        exit(-1);
    }

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

    char buf[100];
    while(1)
    {
     

        Listen(socket_fd, 5);

       
        struct sockaddr_in client_addr;
        unsigned int size = sizeof(client_addr);

        puts("waiting for accept... ...");
        int client_fd = Accept(socket_fd, (struct sockaddr *)&client_addr, &size);

        printf("client : port:%u , addr:%s\n\n",\
               ntohs(client_addr.sin_port), inet_ntoa(client_addr.sin_addr));



    }


    // 回收资源
    pthread_join(tid, NULL);
    Close(socket_fd);

    return 0;
}//end of te main


