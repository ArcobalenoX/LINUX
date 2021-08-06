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

/*********Packgage function myheader****/
#include "Package.h"



int main(int argc,char **argv)
{

    int server_port = 50000;

    //1. 创建套接字
    int socket_fd = Socket(AF_INET, SOCK_STREAM, 0);

    //2. 绑定
    struct sockaddr_in tcp_addr;

    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(server_port);
    tcp_addr.sin_addr.s_addr = inet_addr("192.168.12.210");

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
		   
    int flag=fcntl(client_fd,F_GETFL);
    fcntl(client_fd,F_SETFL,flag|O_NONBLOCK);
	
    char buf[100];
    while(1)
    {
        memset(buf,0,100);
        //   int ret = recv(client_fd, buf, 100, MSG_DONTWAIT);

        int ret = recv(client_fd, buf, 100, 0);
        if(ret == -1)
        {
            if(errno == EAGAIN || errno == EWOULDBLOCK)
            {

                puts("no data recv");
                sleep(1);
            }
            else
            {
                puts("recv erro");
                break;
            }

        }

        printf("recv: %s",buf);

        if(!strncmp(buf, "exit", 4))
        {
            break;
        }
    }


    // 回收资源
    Close(socket_fd);

    return 0;
}//end of te main


