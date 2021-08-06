#include<stdio.h>
#include<sys/types.h>         
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#define IP "127.0.0.1"
#define PORT 8888

int main()
{
	
	int socketfd = socket(AF_INET,SOCK_STREAM,0);
	if(socketfd == -1)
	{
		printf("create socket is fail!\n");
		return -1;
	}
	printf("create socket is success!\n");
/*link*/

	struct sockaddr_in ser_addr;
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(PORT);
	ser_addr.sin_addr.s_addr = inet_addr(IP);
	
	if(connect(socketfd,(struct sockaddr *)&ser_addr,sizeof(ser_addr)) == -1)
	{
		printf("connect");
		return -1;
	}
	printf("connect success!\n");
	
	char buff_send[1024];
	char buff_recv[1024];
/*send*/
	
	while(fgets(buff_send,sizeof(buff_send),stdin))
	{
		if(strncmp(buff_send,"quit",4) == 0)
		{
			printf("client will shutdown!\n");
			break;
		}
		send(socketfd,buff_send,sizeof(buff_send),0);
	}

	
	
/*recv*/


	int accept_fd = accept(socketfd,NULL,NULL);
	if(accept_fd == -1)
	{
		printf("accept fail");
		return -1;
	}
	printf("accept success!\n");

	int recv_byte;
	while(1)
	{
		recv_byte = recv(accept_fd,buff_recv,sizeof(buff_recv),0);
		if(-1 == recv_byte)
		{
			printf("recv fail!\n");
			break;
		}
		if(0 == recv_byte)
		{
			printf("client shutdown!\n");
			break;
		}
		
		printf("recv:%s\n",buff_recv);
	}
	close(accept_fd);
	close(socketfd);


	return 0;
}











