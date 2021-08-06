#include <stdio.h>
#include <sys/types.h>    
#include <sys/socket.h>
#include <arpa/inet.h>


int main()
{
	//创建套接字
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket failed");
		return -1;
	}
	
	//创建结构体
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port =  htons(40000);
	myaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	//绑定"0.0.0.0"表示可以接收任意IP的发送的数据
	
	//绑定
	int lenth = sizeof(struct sockaddr_in);
	bind(sockfd,(struct sockaddr *)&myaddr,lenth);
	
	//监听
	listen(sockfd,3);
	
	//接收通信请求
	struct sockaddr_in srcaddr;
	int sockfd2 = accept(sockfd,(struct sockaddr *)&srcaddr,&lenth);
	
	char buf[24];
	while(1)
	{
		//接收数据
		recv(sockfd2,buf,24,0);
		printf("recv buf=%s\n",buf);
		//发送数据
		send(sockfd2,buf,24,0);
		printf("send buf=%s\n",buf);
	}
	
	
	
	
	return 0;
}