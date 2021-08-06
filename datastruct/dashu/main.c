#include "list.h"

PNode input()
{
    PNode head=list_init();
    char s[50];
    bzero(s,50);
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
        list_add_tail(head,new);
    }

    return head;
}


PNode add(PNode head1,PNode head2)
{
    PNode result=list_init();
    PNode tmp1,tmp2,new;
    int carry=0;
    int i=0;
    tmp1=head1->next;
    tmp2=head2->next;
    while(tmp1!=head1||tmp2!=head2)
    {
        if(tmp1==head1)
            tmp1->data=0;
        if(tmp2==head2)
            tmp2->data=0;
        printf("[%d]--%04d+%04d+%d=%04d\n",i++,tmp1->data,tmp2->data,carry,new->data);

        PNode new=calloc(1,sizeof(Node));
        new->data = tmp1->data + tmp2->data + carry;
        if(new->data >= 10000)
        {
            new->data -=10000;
            carry=1;
        }
        else
        {
            carry=0;
        }
        list_add_head(result,new);

        if(tmp1!=head1)
            tmp1=tmp1->next;
        if(tmp2!=head2)
            tmp2=tmp2->next;
    }

    if(carry==1)
    {
        for(; tmp1!=head1; head1=head1->next)
        {
            if(carry ==1)
            {
                tmp1->data +=carry;
                carry=0;
            }
            else if(carry==0)
            {
                break;
            }

            if(tmp1->data==10000)
            {
                tmp1->data-=10000;
                carry=1;
            }
        }

        if((tmp1 == head1) && (carry== 1))
        {

            PNode new = (PNode)calloc(1,sizeof(Node));
            new->data = 1;

            list_add_head(result,new);
        }

    }
    return result;
}

PNode mul(PNode head1,PNode head2)
{
    PNode result=list_init();
    PNode tmp1,tmp2,new;
    int carry=0;
    int i=0;
    tmp1=head1->next;
    tmp2=head2->next;
    while(tmp1!=head1||tmp2!=head2)
    {
        if(tmp1==head1)
            tmp1->data=0;
        if(tmp2==head2)
            tmp2->data=0;
        printf("[%d]--%04d*%04d+%d=%04d\n",i++,tmp1->data,tmp2->data,carry,new->data);

        PNode new=calloc(1,sizeof(Node));
        new->data = tmp1->data * tmp2->data + carry;
        if(new->data >= 10000)
        {
            new->data %=10000;
            carry=new->data/10000;
        }
        else
        {
            carry=0;
        }
        list_add_head(result,new);

        if(tmp1!=head1)
            tmp1=tmp1->next;
        if(tmp2!=head2)
            tmp2=tmp2->next;
    }

    if(carry==1)
    {
        for(; tmp1!=head1; head1=head1->next)
        {
            if(carry ==1)
            {
                tmp1->data +=carry;
                carry=0;
            }
            else if(carry==0)
            {
                break;
            }

            if(tmp1->data==10000)
            {
                tmp1->data-=10000;
                carry=1;
            }
        }

        if((tmp1 == head1) && (carry== 1))
        {

            PNode new = (PNode)calloc(1,sizeof(Node));
            new->data = 1;

            list_add_head(result,new);
        }

    }
    return result;
}



int main ()
{
    system("clear");
    printf("------------大位数四则运算------------\n");
//    printf("加(a)\t减(s)\t乘(m)\t除(d)\t退出(q)\n");
    PNode head1,head2,result;

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
                    puts("input first num");
                    head1=input();
                    puts("input second num");
                    head2=input();
                    list_show(head1);
                    list_show(head2);
                    result=mul(head1,head2);
                    result_show(result);


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