#ifndef __LIST_H
#define __LIST_H


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


typedef struct _node{
	
	int x , y;

	struct _node *next , *prev;

}Node, *PNode;


PNode list_init(void);

void list_add_head(PNode head, PNode new);

void list_add_tail(PNode head, PNode new);

void list_free(PNode head);

void list_del_tail(PNode head);

void list_del(PNode head,int x,int y);












#endif //end of __LIST_H


