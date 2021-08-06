#ifndef __MYLIST_H
#define __MYLIST_H


/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>

/*******TCP/UDP/IP header**************/
#define  _PG_IP
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


typedef struct _node
{

    in_port_t port;
    struct in_addr addr;
    int fd;
    char name[100];

    struct _node *prev, *next;

} Node, *PNode;


PNode list_init(void)
{

    PNode head = (PNode)Calloc(1, sizeof(Node));

    head->prev = head->next = head;

    return head;
}

void list_add(PNode head, PNode new)
{

    new->prev = head->prev;
    new->next = head;

    head->prev->next = new;
    head->prev =  new;

    ++head->fd;
}


void list_del(PNode head, int fd_del)
{

    PNode tmp;

    for(tmp = head->next; tmp != head; tmp = tmp->next)
    {
        if(tmp->fd == fd_del)
        {
            break;
        }
    }

    if(tmp == head)
    {
        puts("not find");
    }
    else
    {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        free(tmp);
    }

    --head->fd;
}


void list_free(PNode head)
{
	if(head==NULL)
		return;

    PNode tmp1, tmp2;


    //改造非循环链表
    head->prev->next = NULL;


    for(tmp1 = head, tmp2 = tmp1->next;  tmp2 != NULL; \
            tmp1 = tmp2, tmp2 = tmp2->next)
    {

        free(tmp1);
    }

    free(tmp1);

}


void list_pri(PNode head)
{

    PNode tmp;
    puts("");
    for(tmp = head->next; tmp != head; tmp = tmp->next)
    {

        printf("name:%s\t(IP:%s  port:%hu)\n",tmp->name, inet_ntoa(tmp->addr), ntohs(tmp->port));
    }
    puts("");

}


int list_fd_seek(PNode head, PNode SNode)
{

    PNode tmp;

    for(tmp = head->next; tmp != head; tmp = tmp->next)
    {

        if((tmp->port == SNode->port)  && (tmp->addr.s_addr == SNode->addr.s_addr) )
        {

            return tmp->fd;
        }
        if(!strcmp(tmp->name,SNode->name))
            return tmp->fd;
    }

    return -1;
}


void sendfile(int socket_fd,char * filename)
{
    char buf[100];
    struct stat status;

    int fd_file = Open(filename,O_RDONLY);
    fstat(fd_file, &status);

    Send(socket_fd, &status.st_size, 4, 0);

    int i;
    for(i=0; i<status.st_size/100; i++ )
    {

        read(fd_file, buf, 100);
        Send(socket_fd, buf, 100, 0);
    }

    read(fd_file, buf, status.st_size%100);
    Send(socket_fd, buf, status.st_size%100, 0);

	close(fd_file);
}


void recvfile(int socket_fd,char * filename)
{
    char buf[100];
    memset(buf,0,100);
    off_t nbyte;
    Recv(socket_fd, &nbyte, 4, 0);
    int fd_file = Open("recv.txt",O_WRONLY|O_CREAT, 0666);

    int i;
    for(i=0; i<nbyte/100; i++)
    {
        Recv(socket_fd, buf, 100, 0);
        write(fd_file, buf, 100);
    }

    Recv(socket_fd, buf, nbyte%100, 0);
    write(fd_file, buf, nbyte%100);

	close(fd_file);
}




#endif //end of __MYLIST_H

