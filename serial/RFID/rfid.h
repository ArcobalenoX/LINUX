#ifndef __rfid_
#define __rfid_

#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>
#include <termios.h> 
#include <sys/types.h>
#include <sys/select.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <time.h>

static struct timeval timeout;
#define DEV_PATH   "/dev/ttySAC2"

//获取卡号
//参数：存贮卡号的指针
//返回值： 0成功   -1失败
int GetRfId(unsigned int *cardid);


#endif