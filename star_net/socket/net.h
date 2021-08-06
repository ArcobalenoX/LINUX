/**
*	@File name:net.h
*	@Author:岳秀超 17691051169
*	@Date:2019.5.20
*	@Vision:1.0
*	@brief:简单聊天程序的客户端头文件
*
**/

#ifndef __NET_H
#define __NET_H

/********std header**********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <errno.h>

/**********IO header*************/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

/*******TCP/UDP/IP header**************/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/**********pthread header*************/
#include <pthread.h>

#define SERVER_TCP_PORT 50000
#define SERVER_UDP_PORT 50001

#define CLIENT_TCP_PORT 50001
#define CLIENT_UDP_PORT 50011

#define BUF_SIZE 100

#endif //end of __NET_H

