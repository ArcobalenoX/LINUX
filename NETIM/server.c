#include <stdio.h>
#include <sys/types.h>    
#include <sys/socket.h>
#include <arpa/inet.h>


int main()
{
	//�����׽���
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket failed");
		return -1;
	}
	
	//�����ṹ��
	struct sockaddr_in myaddr;
	myaddr.sin_family = AF_INET;
	myaddr.sin_port =  htons(40000);
	myaddr.sin_addr.s_addr = inet_addr("0.0.0.0");
	//��"0.0.0.0"��ʾ���Խ�������IP�ķ��͵�����
	
	//��
	int lenth = sizeof(struct sockaddr_in);
	bind(sockfd,(struct sockaddr *)&myaddr,lenth);
	
	//����
	listen(sockfd,3);
	
	//����ͨ������
	struct sockaddr_in srcaddr;
	int sockfd2 = accept(sockfd,(struct sockaddr *)&srcaddr,&lenth);
	
	char buf[24];
	while(1)
	{
		//��������
		recv(sockfd2,buf,24,0);
		printf("recv buf=%s\n",buf);
		//��������
		send(sockfd2,buf,24,0);
		printf("send buf=%s\n",buf);
	}
	
	
	
	
	return 0;
}