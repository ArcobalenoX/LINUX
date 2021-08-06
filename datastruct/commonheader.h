#ifndef _COMMONHEADER_H_
#define _COMMONHEADER_H_

/**普通操作**/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<string.h>
#include<strings.h>
#include<errno.h>
#include<time.h>

/**文件与目录操作**/
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<dirent.h>

/**进程间通信**/
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<sys/msg.h>
#include<sys/wait.h>
#include<semaphore.h>
#include<signal.h>

/**线程**/
#include<pthread.h>

/**网络**/
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>



#endif