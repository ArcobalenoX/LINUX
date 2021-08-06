#ifndef __LIST_H
#define __LIST_H

#include "kernellist.h"


typedef struct _Node
{
    int data;
    struct list_head K;
} Node,*PNode;

PNode list_init(void)
{
    PNode head =calloc(1,sizeof(Node));
	head->data=0;
    INIT_LIST_HEAD(&head->K);
    return head;
}

void list_add_tail(PNode head,PNode new)
{
	head->data++;
    LIST_ADD_TAIL(&head->K,&new->K);
}
void list_add_head(PNode head,PNode new)
{
	head->data++;
    LIST_ADD_HEAD(&head->K,&new->K);
}

void list_show(PNode head)
{
    struct list_head *tmp;
    PNode BIGADDR;
    int i=0;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Node,K);
        printf("[%d]--%04d\n",i++,BIGADDR->data);
    }
}

void result_show(PNode head)
{
    struct list_head *tmp;
    PNode BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Node,K);
        printf("%04d",BIGADDR->data);
    }
    puts("\n");

}

void list_free(PNode head)//释放所有节点
{
    struct list_head *p,*q;
    PNode BIGADDR;
    int i=0;
    LIST_FOR_EACH_SAFE(p,q,&(head->K))//q保存下一个需要释放的节点
    {
        BIGADDR = GetBig(p,Node,K);
        free(BIGADDR);
    }
    BIGADDR = GetBig(p,Node,K);
    free(BIGADDR);
    free(head);
}

#endif