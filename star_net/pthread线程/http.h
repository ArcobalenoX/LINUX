/**
*
*	@File Name:http.h
*	@Author:岳秀超 17691051169
*	@Version:1.0
*	@Brief:http下载头文件
*	@Date:2019.6.3
*
**/

#ifndef __HTTP2_H
#define __HTTP2_H


/**
*
*	@File Name:
*	@Author:
*	@Version:
*	@Brief:
*	@Date:
*	@Note:
*	@Warning:
*	@Detail:
*	@Undone:
*
**/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <netdb.h>
#include<time.h>
#include <errno.h>
#define _GNU_SOURCE

int http_download(char *url, char *save_path);

#endif //end of __HTTP2_H

