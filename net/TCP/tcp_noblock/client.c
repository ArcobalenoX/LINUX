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


	int client_port = atoi(argv[1]);
	int server_port = 50000;
	if((client_port < 50000) || (server_port < 50000)){
		fprintf(stderr, "prot >= 50000\n");
		exit(-1);
	}


	//1. 创建套接字
	int socket_fd = Socket(AF_INET, SOCK_STREAM, 0);


	//2. 绑定
	struct sockaddr_in tcp_addr;

	tcp_addr.sin_family = AF_INET;
	tcp_addr.sin_port = htons(client_port);
	tcp_addr.sin_addr.s_addr = inet_addr("192.168.12.210");

	Bind(socket_fd, (struct sockaddr *)&tcp_addr, sizeof(tcp_addr));


	//3. 连接服务器
	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(server_port);
	server_addr.sin_addr.s_addr = inet_addr(argv[2]);
	
	Connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	//4. 循环发送数据
	char buf[100];
	while(1){
		memset(buf, 0, 100);
		fgets(buf,100,stdin);

		Send(socket_fd, buf, strlen(buf), 0);
		
		if(!strncmp(buf,"exit",4)){
			break;
		}
	}


	// 回收资源
	Close(socket_fd);

	return 0;
}//end of te main


