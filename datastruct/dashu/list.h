#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <errno.h>
#include <stdarg.h>

typedef struct _Node
{
    int data;
    struct _Node* next;
    struct _Node* prev;
} Node,*PNode;

PNode list_init(void)
{
    PNode head =calloc(1,sizeof(Node));
    head->data=0;
    head->prev=head;
    head->next=head;
    return head;
}

void list_add_tail(PNode head,PNode new)
{

    new->prev=head->prev;
    new->next=head;
    head->prev=new;
    new->prev->next=new;

    head->data++;
}
void list_add_head(PNode head,PNode new)
{

    new->next=head->next;
    new->prev=head;
    head->next->prev=new;
    head->next=new;

    head->data++;
}

void list_show(PNode head)
{
    PNode tmp;
    int i=0;
    for(tmp=head->next; tmp!=head; tmp=tmp->next)
    {
        printf("[%d]--%04d\n",i++,tmp->data);
    }
}

void result_show(PNode head)
{

    PNode tmp;
    for(tmp=head->next; tmp!=head; tmp=tmp->next)
    {
        printf("%04d",tmp->data);
    }
    puts("\n");

}

void list_free(PNode head)//释放所有节点
{
    PNode p,q;
    for(p=head,q=p->next; q!=head; p=q,q=q->next)
    {
        free(p);
    }
    free(p);

}

#endif