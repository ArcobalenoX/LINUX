#ifndef __KERNELLIST_H_
#define __KERNELLIST_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

/*
SmallAddr   小结构体地址
BigName		大结构体类型名
SmallName	小结构体变量名

*/
#define GetBig(SmallAddr,BigName,SmallName) \
		(BigName*)((void*)SmallAddr - (void*)&((BigName*)0)->SmallName)


#define LIST_FOR_EACH(tmp,head) \
		for(tmp=(head)->next; tmp!=(head); tmp=tmp->next)
    
#define LIST_FOR_EACH_SAFE(p,q,head)\
		for(p=(head),q=p->next; q!=(head); p=q,q=q->next )
        
#define INIT_LIST_HEAD(head) \
	{(head)->prev=(head); (head)->next=(head);}



struct list_head
{
    struct list_head *prev;
    struct list_head *next;

};

/*
nd1.K.next=&(nd2.K);
nd2.K.prev =&(nd1.K);
//big = nd1
PNode big = (PNode)( (void*)nd2.K.prev  -  (void*)&((PNode)0->K) );

//big = nd2
PNode big = (PNode)( (void*)nd1.K.next  -  (void*)&((PNode)0->K) );

*/



void INSERT_FRONT(struct list_head * anchor,struct list_head * node)//node插入到anchor前
{
    node->prev=anchor->prev;
    node->next=anchor;
    anchor->prev=node;
    node->prev->next=node;
}

void INSERT_BEHIND(struct list_head * anchor,struct list_head * node)//node插入到anchor后
{
    node->prev=anchor->prev;
    node->next=anchor;
    anchor->prev=node;
    node->prev->next=node;
}




void LIST_ADD_HEAD(struct list_head *head,struct list_head *new)
{
    new->next=head->next;
    new->prev=head;

    head->next->prev=new;
    head->next=new;

}

void LIST_ADD_TAIL(struct list_head *head,struct list_head *new)
{
    new->prev=head->prev;
    new->next=head;
    head->prev=new;
    new->prev->next=new;

}






void LIST_DEL(struct list_head *del)
{
    del->prev->next= del->next;
    del->next->prev=del->prev;

}





#endif
