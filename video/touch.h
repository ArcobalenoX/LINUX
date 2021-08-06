#ifndef __TOUCH_H
#define __TOUCH_H

/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
#include <errno.h>
#include <stdarg.h>

/**********IO header*************/
#define  _PG_IO
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>



#include <linux/input.h> //输入子系统头文件


void get_xy(int* ,int*);
#endif //end of __TOUCH_H

