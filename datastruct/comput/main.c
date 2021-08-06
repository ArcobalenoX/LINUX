#include "list.h"

PNode input()
{
    PNode head=list_init();
    char s[50];
    char *p;
    int i,j,n;
    scanf("%s",s);
    p=&s[strlen(s)-1];
    for(i=strlen(s)-1; i>=0; i=i-4)
    {
        PNode new=calloc(1,sizeof(Node));
        for(j=0; j<4&&*p!=s[-1]; j++)
        {
            n=*p-'0';
            n*=pow(10,j);
            new->data+=n;
            p--;
        }
		head->data++;
        list_add_tail(head,new);
    }

    return head;
}


PNode add(PNode head1,PNode head2)
{
    PNode result=list_init();
    struct list_head *tmp1;
    struct list_head *tmp2;
    PNode BIGADDR1;
    PNode BIGADDR2;
    PNode new;
    int carry=0;
    int i=0;

    tmp1=(&head1->K)->next;
    tmp2=(&head2->K)->next;
    while(tmp1!=(&head1->K)||tmp2!=(&head2->K))
    {
        if(tmp1==(&head1->K))
            BIGADDR1->data=0;
        else
        {
            BIGADDR1 = GetBig(tmp1,Node,K);
            tmp1=tmp1->next;
        }

        if(tmp2==(&head2->K))
            BIGADDR2->data=0;
        else
        {
            BIGADDR2 = GetBig(tmp2,Node,K);
            tmp2=tmp2->next;
        }

        PNode new=calloc(1,sizeof(Node));
        new->data = BIGADDR1->data + BIGADDR2->data + carry;
        carry=0;
        if(new->data >= 10000)
        {
            new->data -=10000;
            carry=1;
        }
        printf("[%d]--%04d+%04d=%04d\n",i++,BIGADDR1->data,BIGADDR2->data,new->data);
        list_add_head(result,new);

    }
    return result;
}

PNode sub(PNode head1,PNode head2)
{
    PNode result=list_init();
    struct list_head *tmp1;
    struct list_head *tmp2;
    PNode BIGADDR1;
    PNode BIGADDR2;
    PNode new;
    int carry=0;
    int flag=0;
    int i=0;

    tmp1=(&head1->K)->next;
    tmp2=(&head2->K)->next;
    while(tmp1!=&(head1->K)||tmp2!=&(head2->K))
    {
        if(tmp1==(&head1->K))
        {
            BIGADDR1->data=0;
            flag=-1;
        }
        else
        {
            BIGADDR1 = GetBig(tmp1,Node,K);
            tmp1=tmp1->next;
        }

        if(tmp2==(&head2->K))
        {
            BIGADDR2->data=0;
            flag=1;
        }
        else
        {
            BIGADDR2 = GetBig(tmp2,Node,K);
            tmp2=tmp2->next;
        }

        PNode new=calloc(1,sizeof(Node));
        new->data = BIGADDR1->data - BIGADDR2->data + carry;
        printf("[%d]--|%04d-%04d|=%04d\n",i++,BIGADDR1->data,BIGADDR2->data,new->data);
        carry=0;
        if(new->data < 0)
        {
            new->data =new->data+10000;
            carry=-1;
        }

        list_add_head(result,new);
    }

    return result;
}

int main ()
{
    system("clear");
    printf("------------大位数四则运算------------\n");
//    printf("加(a)\t减(s)\t乘(m)\t除(d)\t退出(q)\n");
    PNode head1,head2,result;
    head1=list_init();
    head2=list_init();
    result=list_init();

    char oper;
    while(1)
    {
        printf("加(a)\t减(s)\t乘(m)\t除(d)\t退出(q)\n");
        scanf(" %c",&oper);
        if(oper=='q')
        {
            break;
        }
        else
        {
            switch(oper)
            {
                case'a':
                        puts("input first num");
                    head1=input();
                    puts("input second num");
                    head2=input();
                    list_show(head1);
                    list_show(head2);
                    result=add(head1,head2);
                    result_show(result);
                    break;

                case's':

                    break;

                case'm':

                    break;

                case'd':

                        break;

                default:
                    break;

            }

        }
        list_free(head1);
        list_free(head2);
        list_free(result);
    }


    return 0;
}