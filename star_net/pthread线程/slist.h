/**
*
*	@File Name:slist.h
*	@Author:岳秀超 17691051169
*	@Version:1.0
*	@Brief:任务列表头文件
*	@Date:2019.6.3
*
**/

#ifndef __SLIST_H
#define __SLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/mman.h>
#include <errno.h>
#include <unistd.h>


typedef struct 
{
    void ** items;
    int item_maxcount;
    int item_count;
    int item_size;
} __Z_SLIST;

typedef void* Z_SLIST;


Z_SLIST task_slist_new(int item_size,int item_maxcount);
int task_slist_delete(Z_SLIST list,int idx);
int task_slist_add(Z_SLIST list,const void * item);
int task_slist_insert(Z_SLIST list,const void*item,int idx);
void * task_slist_get(Z_SLIST list,int idx);





#endif //end of __SLIST_H

