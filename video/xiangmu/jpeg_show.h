#ifndef __JPEG_SHOW_H
#define __JPEG_SHOW_H
/********std header**********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>
#include <setjmp.h>

/**********IO header*************/

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>


/********* jpeglib header *************/
#include "jpeglib.h"

int jpeg_show(char * const path);

#endif //end of ___H

