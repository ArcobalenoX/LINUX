/**
*
*	@File Name:slist.c
*	@Author:岳秀超 17691051169
*	@Version:1.0
*	@Brief:任务列表源文件
*	@Date:2019.6.3
*
**/
#include "slist.h"



Z_SLIST task_slist_new(int item_size,int item_maxcount)
{
    __Z_SLIST * list=NULL;
    int itemstotalsize=item_size * item_maxcount;

    list=(__Z_SLIST*)malloc(sizeof(__Z_SLIST));
    list->items=(void**)malloc(itemstotalsize);

    list->item_count=0;
    list->item_maxcount=item_maxcount;
    list->item_size=item_size;
    return (Z_SLIST)list;

}


int task_slist_add(Z_SLIST list,const void * item)
{
    __Z_SLIST* l=(__Z_SLIST*)list;
    if(l->item_count >= l->item_maxcount)
    {
        return -1;

    }


    if(l->item_count < l->item_maxcount)
    {
        memcpy((char*)l->items + l->item_count*l->item_size,item,(int)l->item_size);
        l->item_count++;
    }
    return 0;
}


void * task_slist_get(Z_SLIST list,int idx)
{
    __Z_SLIST* l=(__Z_SLIST*)list;

    if(!(idx>=0 && idx < l->item_count))
    {
        return NULL;

    }
    return (void*)((char*)l->items + idx*l->item_size);

}


int task_slist_delete(Z_SLIST list,int idx)
{
    __Z_SLIST* l=(__Z_SLIST*)list;

    if(idx>=0&&idx<l->item_count)
    {
        int i=0;
        for(i=idx; i<l->item_count-1; i++)
        {
            memcpy((char*)l->items + i*l->item_size,(char*)l->items + (i+1)*l->item_size,(int)l->item_size);
        }
        l->item_count--;

    }
    return 0;

}


int task_slist_insert(Z_SLIST list,const void*item,int idx)
{
    __Z_SLIST* l=(__Z_SLIST*)list;

    if(l->item_count>=l->item_maxcount)
    {
        return -1;

    }


    if(idx>=0 && idx <= l->item_count)
    {
        int i=0;
        for(i=l->item_count; i>idx; i--)
        {
            memcpy((char*)l->items + i*l->item_size,(char*)l->items + (i-1)*l->item_size,(int)l->item_size);
        }
        memcpy((char*)l->items + idx*l->item_size,item,(int)l->item_size);
        l->item_count++;

    }
    return idx;

}































