#ifndef __YUYV_H
#define __YUYV_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>          
#include <fcntl.h>            
#include <unistd.h>
#include <errno.h>
#include <malloc.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <asm/types.h>        
#include <linux/videodev2.h>
#include "jpeglib.h"

#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>
#include <signal.h>

#define OUTPUT_BUF_SIZE  4096
#define CLEAR(x) memset (&(x), 0, sizeof (x))
#define WIDTH 640//320
#define HEIGHT 480//240



#endif //end of __YUYV_H

