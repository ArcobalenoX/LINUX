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
    Listen(socket_fd, 5); //设置一次同时可相应的客户端的数量

    //4. 等待连接
    struct sockaddr_in client_addr[3];
    unsigned int size = sizeof(struct sockaddr_in);
    fd_set readfds;
	fd_set writefds;

    FD_ZERO(&readfds);
	FD_ZERO(&writefds);

    int client_fd[3];
    int i;
    int fd_max = 0;
    for(i=0; i<3; i++)
    {

        puts("waiting for accept... ...");
        client_fd[i] = Accept(socket_fd, (struct sockaddr *)&client_addr[i], &size);

        printf("client : port:%u , addr:%s\n\n",\
               ntohs(client_addr[i].sin_port), inet_ntoa(client_addr[i].sin_addr));

        fd_max = fd_max > client_fd[i] ? fd_max : client_fd[i];
    }

    char buf[100];
    while(1)
    {

        for(i=0; i<3; i++)
        {
            FD_SET(client_fd[i], &readfds);
			
            //printf("client_fd %d  ",client_fd[i]);
        }

        int ret = select(fd_max + 1, &readfds, &writefds, NULL, NULL);

        if(ret == -1)
        {
            printf("select err\n");
        }

        for(i=0; i<3; i++)
        {

            if( FD_ISSET(client_fd[i], &readfds) )
            {

                memset(buf,0,100);
                Recv(client_fd[i], buf, 100, 0);
                printf("recv:[%hu][%s] %s", htons(client_addr[i].sin_port),\
                       inet_ntoa(client_addr[i].sin_addr), buf);

            }
        }
		fgets(buf,100,stdin);
		
		

    }



    // 回收资源


    return 0;
}//end of te main


