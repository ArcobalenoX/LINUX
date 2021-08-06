#ifndef __LCD_H
#define __LCD_H

#include <stdio.h>   	//printf scanf
#include <fcntl.h>		//open write read lseek close  	 
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include "jpeglib.h"

#define LCD_WIDTH  			800
#define LCD_HEIGHT 			480
#define FB_SIZE				(LCD_WIDTH * LCD_HEIGHT * 4)
#define EN_LCD_SHOW_JPG		1

int lcd_draw_jpg(unsigned int x,unsigned int y,const char *pjpg_path,char *pjpg_buf,\
		unsigned int jpg_buf_size,unsigned int jpg_half);

#endif //end of __LCD_H

