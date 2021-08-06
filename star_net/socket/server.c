/**
*	@File name:server.c
*	@Author:岳秀超 17691051169
*	@Date:2019.5.20
*	@Vision:1.0
*	@brief:简单聊天程序的服务器端
*
**/

#include "net.h"


void * routine(void *arg);//发送消息线程
int tcp_socket =0;//本地tcp套接字
int udp_socket =0;//本地udp套接字
void file_recv(int socket_fd);//文件接收
void file_send(int socket_fd);//文件发送
int client_tcp_socket;
void file();
int main(int argc,char **argv)
{

    //tcp_init
    //1. 创建TCP套接字
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(tcp_socket == -1)
    {
        perror("tcp socket fail\n");
        exit(-1);
    }

    //2. 绑定TCP
    struct sockaddr_in tcp_addr;
    tcp_addr.sin_family = AF_INET;
    tcp_addr.sin_port = htons(SERVER_TCP_PORT);
    tcp_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(tcp_socket, (struct sockaddr *)&tcp_addr, sizeof(tcp_addr))	== -1)
    {
        perror("tcp bind fail\n");
        exit(-1);
    }

    //3. 设置监听
    if( listen(tcp_socket,5) == -1)
    {
        perror("tcp listen fail\n");
        exit(-1);
    }

    //4. 等待客户端连接
    struct sockaddr_in client_tcp_addr;
    socklen_t sockaddr_in_size = sizeof(client_tcp_addr);

    puts("waiting for accept... ...");
    client_tcp_socket= accept(tcp_socket,\
                              (struct sockaddr *)&client_tcp_addr, &sockaddr_in_size);

    printf("accept client : addr:%s , port:%u\n\n",\
           inet_ntoa(client_tcp_addr.sin_addr),\
           ntohs(client_tcp_addr.sin_port));


    //udp_init
    //1. 创建UDP套接字
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if(udp_socket == -1)
    {
        perror("udp socket fail\n");
        exit(-1);
    }

    //2.绑定UDP
    struct sockaddr_in udp_addr;
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(SERVER_UDP_PORT);
    udp_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(udp_socket, (struct sockaddr *)&udp_addr, sizeof(struct sockaddr_in)) == -1 )
    {
        perror("udp bind fail\n");
        exit(-1);
    }

    //3. 客户端UDP信息
    struct sockaddr_in client_udp_addr;
    client_udp_addr.sin_family = AF_INET;
    client_udp_addr.sin_addr.s_addr = client_tcp_addr.sin_addr.s_addr;
    client_udp_addr.sin_port = htons(CLIENT_UDP_PORT);


    //创建线程发送消息
    pthread_t tid;
    pthread_create(&tid, NULL, routine, (void *)&client_udp_addr );


    //主线程接收消息
    char buf[BUF_SIZE];
    printf("直接输入则发送文字\n");
    printf("输入\"file\"则传输文件\n");
    while(1)
    {

        memset(buf, 0, BUF_SIZE);
        recvfrom(udp_socket, buf, BUF_SIZE, 0, \
                 (struct sockaddr *)&client_udp_addr, &sockaddr_in_size);
        printf("recv:%s\n",buf);
        if(!strncmp(buf, "exit", 4))
        {
            printf("client have exit!!!\n");
            break;
        }
        if(!strncmp(buf, "file", 4))
        {
            printf("client send file!!!\n");
            file_recv(client_tcp_socket);
        }

    }


    //资源回收
    pthread_cancel(tid);
    close(client_tcp_socket);
    close(tcp_socket);
    close(udp_socket);
    return 0;
}//end of te main

void * routine(void *arg)
{
    struct sockaddr_in client_udp_addr=*(struct sockaddr_in*)arg;
    socklen_t sockaddr_in_size = sizeof(client_udp_addr);

    char buf[BUF_SIZE];
    while(1)
    {
        memset(buf, 0, BUF_SIZE);
        fgets(buf,BUF_SIZE,stdin);
        sendto(udp_socket, buf, BUF_SIZE, 0, \
               (struct sockaddr *)&client_udp_addr, sockaddr_in_size);
        if(!strncmp(buf, "exit", 4))
        {
            break;
        }
        if(!strncmp(buf,"file",4))
        {
            printf("server send file!!!\n");
			file_send(client_tcp_socket);

        }

    }
    pthread_exit(0);
}


void file_recv(int socket_fd)  //接收文件
{

    int	tcp_fd =socket_fd;
    char file_name[256] = {0};
    char buf[100] = {0};
	
    //接收文件的大小
    off_t file_size=0;
    recv(tcp_fd, &file_size, sizeof(off_t), 0);
    printf("recv file size: %lu\n", file_size);
	
	//接收文件名字
    recv(tcp_fd, buf, 100, 0);
    printf("recv file name: %s\n",buf);
    sprintf(file_name,"%s_%s","server_recv",buf);	

    //接收文件的内容
    int fd_file;
    fd_file = open(file_name, O_CREAT|O_WRONLY, 0666);
	if(fd_file == -1)
	{
		perror("open file fail\n");
		return;
	}
    int RecvSize = 0;
    while( RecvSize < file_size)
    {
        memset(buf, 0, 100);
        int ret = recv(tcp_fd, buf, 100, 0);
        RecvSize += ret;
        write(fd_file, buf, ret);
    }

    //回收资源
    close(fd_file);
    printf("recv file over!!!\n");
    return;
}
void file_send(int socket_fd)
{
    int tcp_fd=socket_fd;
    char file_name[256] = {0};

 
    printf("input file name \n");
    scanf("%s",file_name);



    int fd_file = open(file_name, O_RDONLY);
	if(fd_file == -1)
	{
		perror("open file fail\n");
		return;
	}
	printf("start send file %s******\n",file_name);
	//发送文件的大小
    struct stat file_info;
    fstat(fd_file, &file_info);
    send(tcp_fd, &file_info.st_size, sizeof(off_t), 0);
    printf("send file_size: %lu\n",file_info.st_size);
	
	
	//发送文件名字
    send(tcp_fd, file_name, strlen(file_name), 0);
	
    //发送文件内容
    char * buf = (char *)calloc(1, file_info.st_size);
    read(fd_file, buf, file_info.st_size);
    send(tcp_fd, buf, file_info.st_size, 0);

    //回收资源
    free(buf);
    close(fd_file);
    printf("send file over!!!\n");
    return;
}


