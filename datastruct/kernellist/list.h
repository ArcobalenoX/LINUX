#ifndef __LIST_H
#define __LIST_H

#include "kernellist.h"

//#define _Node student


typedef struct _Node
{
    int data;
    char num[8];
    char color;
    struct list_head K;


} Node,*PNode;



PNode list_init(void)
{
    PNode head =calloc(1,sizeof(Node));

    INIT_LIST_HEAD(&head->K);
	return head;

}

void list_add(PNode head,PNode new)
{
    //LIST_ADD_HEAD(&head->K,&new->K);
    LIST_ADD_TAIL(&head->K,&new->K);

}

void list_show(PNode head)
{
    struct list_head *tmp;
    PNode BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Node,K);
        printf("序列号%d\t",BIGADDR->data);
        printf("车牌号%s\t",BIGADDR->num);
        switch(BIGADDR->color)
        {
            case '0':
                printf("颜色--黑色\n");
                break;
            case '1':
                printf("颜色--白色\n");
                break;
            case '2':
                printf("颜色--绿色\n");
                break;
            case '3':
                printf("颜色--红色\n");
                break;
            case '4':
                printf("颜色--蓝色\n");
                break;
            case '5':
                printf("颜色--黄色\n");
                break;
            default:
                printf("颜色--【无】\n");

        }
    }

}



void list_seek_data(PNode head,int data)
{
    struct list_head *tmp;
    PNode BIGADDR;
    int i=0;
    LIST_FOR_EACH(tmp,&head->K)
    {
        ++i;
        BIGADDR = GetBig(tmp,Node,K);
        if(BIGADDR->data==data)
        {
            printf("data be found on %dth\n",i);
            break;
        }
    }
    if(tmp==&head->K)
    {
        puts("not found");
    }

}

void list_seek_num(PNode head,char s[8])
{
    struct list_head *tmp;
    PNode BIGADDR;
    int i=0;
    LIST_FOR_EACH(tmp,&head->K)
    {
        ++i;
        BIGADDR = GetBig(tmp,Node,K);
        if(!strcmp(BIGADDR->num,s))
        {
            printf("num be found on %dth\n",i);
            break;
        }
    }
    if(tmp==&head->K)
    {
        puts("not found");
    }

}


void list_del_data(PNode head,int data)
{
    struct list_head *tmp;
    PNode BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Node,K);
        if(BIGADDR->data==data)
        {
            printf("%d will be del\n",data);
            LIST_DEL(&BIGADDR->K);
            free(BIGADDR);
            break;
        }
        if(tmp==&head->K)
        {
            puts("not found");
        }

    }

}


void list_del_num(PNode head,char s[8])
{
    struct list_head *tmp;
    PNode BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Node,K);
         if(!strcmp(BIGADDR->num,s))
        {
            printf("%s will be del\n",s);
            LIST_DEL(&BIGADDR->K);
            free(BIGADDR);
            break;
        }
        if(tmp==&head->K)
        {
            puts("not found");
        }

    }

}





void list_free(PNode head)//释放所有节点
{
    struct list_head *p,*q;
    PNode BIGADDR;

    LIST_FOR_EACH_SAFE(p,q,&(head->K))//q保存下一个需要释放的节点
    {
        BIGADDR = GetBig(p,Node,K);

        if(p!=&(head->K))
        {
            printf("free:data-->%d\n",BIGADDR->data);
        }
        free(BIGADDR);
    }

    BIGADDR = GetBig(p,Node,K);
    printf("free:data-->%d\n",BIGADDR->data);
    free(BIGADDR);

    free(head);
}









#endif