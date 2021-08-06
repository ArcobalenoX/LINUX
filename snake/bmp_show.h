#ifndef __BMP_SHOW_H
#define __BMP_SHOW_H


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



/********** divce driver header ********/


void bmp_show(char *path_name, int ,int);
void bmp_show_bck(char *path_name, int ,int);


#endif //end of __BMP_SHOW_H

