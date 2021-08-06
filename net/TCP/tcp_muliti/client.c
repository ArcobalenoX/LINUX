/*client*/
#include "net.h"

#define SERVER_PORT 50000

#define BUFFER_SIZE 1024

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


void *routine(void *arg)
{
    int fd=*(int *)arg;

    //接收消息
    char recvbuf[100];
    while(1)
    {
        memset(recvbuf,'\0',sizeof(recvbuf));
        int ret=recv(fd,recvbuf,100,0);
        if(ret==-1||ret==0)
        {
            perror("recv");
            exit(-1);
        }

        display_time();
        printf("received  from server:\n%s",recvbuf);
        if(strncmp(recvbuf, "quit",4) == 0)
        {
            printf("server had quit!!!\n");
            exit(-1);
        }
    }

}

int main(int argc,char*argv[])
{

    if(argc != 3)
    {
        printf("usage:%s [self_port] [ipv4]\n",argv[0]);
        exit(-1);
    }
    system("clear");


    int sockfd;
    /*创建socket*/
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    /*绑定socket*/
    struct sockaddr_in client_addr;
    client_addr.sin_family =AF_INET;
    client_addr.sin_port = htons(atoi(argv[1]));
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);//"0.0.0.0"
    //client_addr.sin_addr.s_addr=inet_addr("192.168.12.210");
    bind(sockfd,(struct sockaddr*)&client_addr,sizeof(client_addr));


    /*对服务器端的连接*/
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERVER_PORT);
    serv_addr.sin_addr.s_addr =inet_addr(argv[2]);
    connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr));


    //线程负责消息的接收
    pthread_t tid;
    pthread_create(&tid,NULL,routine,&sockfd);

    char sendbuf[BUFFER_SIZE];
    //发送消息
    while(1)
    {
        memset(sendbuf,'\0',sizeof(sendbuf));
        display_time();
        fgets(sendbuf, sizeof(sendbuf), stdin);
        send(sockfd,sendbuf,strlen(sendbuf),0);
        if(strcmp(sendbuf, "quit\n") == 0)
            break;
    }

    pthread_join(tid,NULL);

    close(sockfd);

    return 0;
}