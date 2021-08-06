/*server*/
#include "net.h"

#define PORT 50000
#define BUFFER_SIZE 1024

struct msg
{
    int fd;
    in_port_t      port;	/* port in network byte order */
    struct in_addr addr;	/* internet address */
};

void display_time()
{
    time_t t;
    t = time(NULL);
    struct tm *p = localtime(&t);

    printf("%d-",1900+ p->tm_year);//Year  需要加上1900
    printf("%d-",1+p->tm_mon);//Month  需要加上1
    printf("%d  ",p->tm_mday);//Day
    printf("%d:",p->tm_hour);//Hour
    printf("%d:",p->tm_min);//Minute
    printf("%d\n",p->tm_sec);//Second

}



void *recvroutine(void *arg)
{
    struct msg message=*(struct msg*)arg;
    int fd=message.fd;
    int ret;
    //接收消息
    char recvbuf[BUFFER_SIZE];
    while(1)
    {
        memset(recvbuf,'\0',sizeof(recvbuf));
        ret=recv(fd,recvbuf,BUFFER_SIZE,0);
        if(ret==-1||ret==0)
        {
            perror("no recv");
            exit(-1);
        }

        display_time();
        printf("received from %s %u:\n%s",inet_ntoa(message.addr),htons(message.port),recvbuf);
        if(strncmp(recvbuf, "quit",4) == 0)
        {
            printf("client had quit!!!\n");
            break;
        }
    }
    close(fd);
    pthread_exit(0);
}


void *sendroutine(void *arg)
{
    char sendbuf[100];
    struct msg message=*(struct msg*)arg;
    int fd=message.fd;
    while(1)
    {
        //发送消息
        memset(sendbuf,'\0',sizeof(sendbuf));
        display_time();
        fgets(sendbuf,sizeof(sendbuf),stdin);
        send(fd,sendbuf,strlen(sendbuf),0);
		
        if(strncmp(sendbuf, "quit",4) == 0)
        {
            close(fd);
            pthread_exit(0);
        }

    }

}
int main(int argc,char*argv[])
{
    system("clear");
    int sockfd;
    struct sockaddr_in server_sockaddr,client_sockaddr;

    /*建立socket连接*/
    sockfd=socket(AF_INET,SOCK_STREAM,0);//SOCK_STREAM---TCP


    /*设置sockaddr_in结构体相关参数，绑定socket*/
    server_sockaddr.sin_family =AF_INET;
    server_sockaddr.sin_port = htons(PORT);//小端转大端
    //server_sockaddr.sin_addr.s_addr = INADDR_ANY;
    server_sockaddr.sin_addr.s_addr = inet_addr("192.168.12.210");

    bind(sockfd,(struct sockaddr*)&server_sockaddr,sizeof(struct sockaddr));

    printf("server: port:%u , addr:%s\n",\
           ntohs(server_sockaddr.sin_port), inet_ntoa(server_sockaddr.sin_addr));

    /*一次监听数量*/
    listen(sockfd,5);
    printf("listening...\n\n");



    int	client_fd;
    struct msg message;
    char sendbuf[BUFFER_SIZE];
    pthread_t tid,tidsend;

    while(1)
    {
        socklen_t length=sizeof(client_sockaddr);
        if((client_fd = accept(sockfd,(struct sockaddr*)&client_sockaddr, &length)) == -1)
        {
            perror("accept");
            exit(-1);
        }
        else
        {
            printf("accept client connect success!\n");
            printf("client : port:%u , addr:%s\n\n",\
                   ntohs(client_sockaddr.sin_port), inet_ntoa(client_sockaddr.sin_addr));

        }


        message.fd=client_fd;
        message.port=client_sockaddr.sin_port;
        message.addr=client_sockaddr.sin_addr;
        pthread_create(&tid,NULL,recvroutine,(void*)&message);


        pthread_create(&tidsend,NULL,sendroutine,(void*)&message);

    }

    close(sockfd);

    return 0;
}