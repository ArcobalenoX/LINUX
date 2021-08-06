/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
#include <sys/mman.h>
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


#include <pthread.h>


/*********Packgage function myheader****/
#include "Package.h"



int main(int argc,char **argv)
{

    if(argc != 2)
    {

        fprintf(stderr, "usage: %s  <rcv_port>  \n",argv[0]);
        exit(-1);
    }

	//1. socket
    int sock_fd = Socket(AF_INET, SOCK_DGRAM, 0);

    //2. bind
    struct sockaddr_in udp_addr;
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    udp_addr.sin_port = htons(atoi(argv[1]));
    Bind(sock_fd, (struct sockaddr *)&udp_addr, sizeof(struct sockaddr_in));

    //3. send msg
    struct sockaddr_in snd_addr;
    socklen_t size = sizeof(snd_addr);
	
	
	
    char buf[100];
    while(1)
    {
        memset(buf, 0, 100);

        recvfrom(sock_fd, buf, 100, 0, \
                 (struct sockaddr *)&snd_addr, &size);

        printf("recv:[ip--%s][port--%hu] %s\n", inet_ntoa(snd_addr.sin_addr), ntohs(snd_addr.sin_port), buf);

        if(!strncmp(buf, "exit", 4))
        {
            break;
        }
    }
  

    close(sock_fd);

    return 0;
}//end of te main



