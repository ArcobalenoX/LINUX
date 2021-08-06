/**

	@file name:单向链表，特定NULL转变为head则为单向循环链表
	
	@date:2019.3.2
	
	@version:
	@modify history:



**/


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

typedef struct list
{
    int data;
    struct list * next;
} SL,*PL;

PL 	init(int data)//数据初始化为节点
{
    PL node=calloc(1,sizeof(SL));
    node->data=data;
    node->next=NULL;
    return node;
}

void tailadd(PL head,PL node)//尾部添加节点
{
    PL p;
    for(p=head; p->next!=NULL; p=p->next);
    p->next=node;

    head->data++;
}

void headadd(PL head,PL node)//头部添加节点
{
    node->next=head->next;
    head->next=node;

    head->data++;
}



void show(PL head)//遍历显示
{
    PL p;
    for(p=head->next; p!=NULL; p=p->next)
    {
        printf("%d\n",p->data);
    }

}

void del(PL head,int data)//删除对应数据的节点
{

    PL p,q;
    for(q=head,p=q->next; p!=NULL; q=p,p=p->next)
    {
        if(p->data==data)
        {
            printf("find data %d \n",p->data);
            q->next=p->next;
            free(p);
        }
        if(p==NULL)
        {
            puts("not found");
        }

    }

}

void freeall(PL head)//释放所有节点
{
    PL p,q;
	
    for(p=head,q=p->next; q!=NULL; q=q->next )
    {
        if(p!=head)
        {
            printf("free:data-->%d\n",p->data);
        }
        free(p);
        p=q;//p指向下一个需要释放的节点

    }
    printf("free:data-->%d\n",p->data);
    free(p);

}

void sort(PL head)/*插入排序*/
{

    if(head == NULL || head->next == NULL)return;
	
    PL p = head->next;
    PL pstart= init(0);
    PL q = head;
	
    pstart->next = head; //为了操作方便，添加一个头结点
    while(p != NULL)
    {
        PL tmp = pstart->next, pre = pstart;
        while( tmp != p && p->data >= tmp->data ) //找到插入位置
        {
            tmp = tmp->next;
            pre = pre->next;
        }
        if(tmp == p)
            q = p;
        else
        {
            q->next = p->next;
            p->next = tmp;
            pre->next = p;
        }
        p = q->next;
    }
    head = pstart->next;
    free(pstart);

}


int main(int argc,char **argv)
{

    PL head=init(0);
    int i;
    for(i=1; i<5; i++)
    {
        PL node=init(i);
        tailadd(head,node);
    }

    for(i=1; i<5; i++)
    {
        PL node=init(10+i);
        headadd(head,node);
    }



    show(head);

//   del(head,2);
//   show(head);

//    sort(head);
//   show(head);


    freeall(head);

    return 0;
}//end of te main


