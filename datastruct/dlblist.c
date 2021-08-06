/**

	@file name:双向(循环)链表
	特定NULL转变为head则为双向循环链表

	@date:2019.3.9

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
    struct list * prev;
} SL,*PL;

typedef enum _RangeType {BIG,SMALL} RangeType;


PL 	init(int data)//数据初始化为节点
{
    PL node=calloc(1,sizeof(SL));
    node->data=data;
    node->next= node;
    node->prev=node;
    return node;
}

void insertfront(PL anchor,PL node)//node插入到anchor前
{
    node->prev=anchor->prev;
    node->next=anchor;
    anchor->prev=node;
    node->prev->next=node;
}

void insertbehind(PL anchor,PL node)//node插入到anchor后
{
    node->prev=anchor->prev;
    node->next=anchor;
    anchor->prev=node;
    node->prev->next=node;
}

void tailadd(PL head,PL node)//尾部添加节点
{
    insertfront(head,node);

    head->data++;
}

void headadd(PL head,PL node)//头部添加节点
{
    insertbehind(head,node);

    head->data++;
}

void show(PL head)//遍历显示
{
    PL p;
    for(p=head->next; p!=head; p=p->next)
        printf("%d\n",p->data);
}

void del(PL head,int data)//删除对应数据的节点
{

    PL p;
    for(p=head->next; p!=head; p=p->next)
    {
        if(p->data==data)
        {
            printf("data--%d will be del\n",p->data);
            p->prev->next=p->next;//p的前一个指向p的后一个
            //if(p->next!=NULL)//不循环链表下p不为最后一个
            p->next->prev=p->prev;//p的后一个指向p的前一个


            free(p);
            head->data--;
        }
        if(p==head)
        {
            puts("not found");
        }
    }
}

void freeall(PL head)//释放所有节点
{
    PL p,q;

    for(p=head,q=p->next; q!=head; q=q->next )
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
    free(head);

}



void joseoh(PL head)//约瑟夫环，每隔两个元素，删除一个
{
    PL tmp=head->next;
    if(tmp==head)
    {
        printf("only head %d\n",tmp->data);
        return;
    }
    int i;
    PL del;
    while(1)
    {
        if( tmp->next==head && tmp->prev==head)
        {
            printf("only %d\n",tmp->data);
            break;
        }
        for(i=0; i<3; i++)//跳到第三个元素
        {
            tmp=tmp->next;
            if(tmp==head)tmp=tmp->next;//特殊情况
        }
        del=tmp->prev;//保存删除元素的前一个

        tmp->prev->next=tmp->next;//删除元素
        tmp->next->prev=tmp->prev;

        printf("free %d\n",tmp->data);
        free(tmp);

        tmp=del;
        if(tmp==head)tmp=tmp->prev;//特殊情况

    }


}



void list_add_small(PL newhead,PL new_node)//由小到大插入
{

    PL t;
    t=newhead->next;
    while( (t!=newhead) && (t->data < new_node->data))
    {
        t = t->next;
    }//new_node小于t，退出循环

    //new_node插到t前面
    insertfront(t,new_node);
}

void list_add_big(PL newhead,PL new_node)//由大到小插入
{

    PL t;
    t=newhead->next;
    while( (t!=newhead) && (t->data > new_node->data))
    {
        t = t->next;
    }//new_node大于t，退出循环

    //new_node插到t前面
    insertfront(t,new_node);
}



PL list_arrage(PL head,RangeType type)//链表排序
{

    PL new_head = init(0);

    PL p,q;
    p=head->next;

    while( p!=head )
    {
        q = p->next;//保存移动的节点
        if(type == BIG)
            list_add_big(new_head,p);
        else if(type == SMALL)
            list_add_small(new_head,p);
        new_head->data++;
        p = q;
    }

    free(head);

    return new_head;
}

void middle(PL head)//找到链表中间的元素
{
    PL p,q;
    p=q=head;
    while( 1 )
    {
        q=q->next;
        if( p=p->next,p->next==head)
        {
            printf("middle is %d\n",p->data);
            break;
        }
        if( p=p->next,p->next==head)
        {
            printf("middle are %d and %d\n",p->data,p->next->data);
            break;
        }
    }


    //已知元素个数求中间元素
    int i,mid=0;
    if(head->data % 2==0)
    {
        mid=head->data/2;
        for(i=0; i<mid+1; i++)
            p=p->next;
        printf("middle are %d and %d\n",p->data,p->next->data);
    }
    else if(head->data % 2==1)
    {
        mid=(head->data+1)/2;
        for(i=0; i<mid+1; i++)
            p=p->next;
        printf("middle is %d\n",p->data);
    }


}


int main(int argc,char **argv)
{
    PL head=init(0);
    int i,t;
    for(i=0; i<5; i++)
    {
        scanf("%d",&t);
        PL node=init(t);

        tailadd(head,node);
    }
    /*
        for(i=1; i<5; i++)
        {
            PL node=init(10+i);

            headadd(head,node);
        }

    */

    show(head);
    /*
        scanf("%d",&i);
        del(head,i);
        show(head);
    */

    middle(head);

    head=list_arrage(head,BIG);
    show(head);

//    joseoh(head);

    freeall(head);
    return 0;
}//end of te main


