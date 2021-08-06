#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#define buf_size 50
typedef struct list
{

    char buf[buf_size];
    struct list * next;
} SL,*PL;

PL 	init(char buf[buf_size])//数据初始化为节点
{
    PL node=calloc(1,sizeof(SL));
    strcpy(node->buf,buf);
    node->next=NULL;
    return node;
}

void tailadd(PL head,PL node)//尾部添加节点
{
    PL p;
    for(p=head; p->next!=NULL; p=p->next);
    p->next=node;
}

void show(PL head)//遍历显示
{
    PL p;

    for(p=head->next; p!=NULL; p=p->next)
    {
        printf("%s",p->buf);

    }

}

void freeall(PL head)//释放所有节点
{
    PL p,q;
    for(p=head,q=p->next; q!=NULL; q=q->next )
    {
        free(p);
        p=q;//p指向下一个需要释放的节点

    }
    free(p);
}


int main(int argc,char **argv)
{

    PL head=init("");
    char string[200]="";
    char buf[buf_size];
    char *ch;
    int i=0,j=0,n=0;
    char t;
    scanf("%s",string);
    ch=string;
    while(*ch!='\0')
    {
        for(j=0; (j<buf_size)&&(*ch!='\0'); j++)
        {

            if(*ch=='Q')
            {
                ch++;
                i++;
                while(*ch>='0'&&*ch<='9')
                {
                    ch++;
                }
                sprintf(buf,"%sText%d",buf,i);

                break;

            }
            buf[j]=*ch++;
        }
        PL node=init(buf);
        tailadd(head,node);
        memset(buf,'\0',buf_size);
    }
    show(head);
    freeall(head);
    return 0;
}


