#include <stdio.h>
#include <stdlib.h>

typedef struct doublelist
{

    int data;
    struct doublelist* next;
    struct doublelist* prev;
}*Doublelist;

Doublelist create_doublelist(int num)
{
    Doublelist node =malloc(sizeof(struct doublelist));

    if(node==NULL)
        perror("malloc faild");
    else
    {
        node->data=num;
        node->next=NULL;
        node->prev=NULL;
    }

    return node;
}

void last_insert(Doublelist head)
{
    Doublelist p;
    int i;
    for(i=0; i<10; i++)
    {
        Doublelist new=create_doublelist(i);
        p=head;
        while(p->next !=NULL)
            p=p->next;
        p->next=new;
        new->prev =p;


    }



}
void front_insert(Doublelist head)//头部添加节点
{
    int i=0;
    for(i=0; i<10; i++)
    {
        Doublelist new = create_doublelist(i);

        if(head->next == NULL)
        {
            head->next = new;
            new->prev = head;
        }

        else
        {
            //next方向上
            new->next = head->next;
            head->next = new;
            //prev方向上
            new->next->prev = new;
            new->prev = head;
        }
    }
}

void scan_insert(Doublelist head)
{
    Doublelist p;




}


void dispaly(Doublelist head)
{
    Doublelist p=head;
    while(p->next !=NULL)
    {
        p=p->next;
        printf("——%d——",p->data);

    }
    printf("\n");
}
int main()
{
    Doublelist head=create_doublelist(0);

    int num;
    while(1)
    {

        scanf("%d",&num);

        if(num>0)
        {

            Doublelist node =create_doublelist(num);
            Doublelist p=head;
            while(p!=NULL)
            {
                p=p->next;
                if(p->data > num)break;

            }
            if(p!=NULL)
            {
                p->prev->next=node;
                node->next=p;
                node->prev=p->prev;
                p->prev=node;
            }
            else
            {
                //再次遍历链表
                p=head;
                while(p->next != NULL)
                    p=p->next;

                p->next = node;
                node->prev = p;
            }
        }


        else if(num<0)
        {

            Doublelist p=head;
            while(p!=NULL)
            {
                p=p->next;
                if((num+p->data)==0)
                    break;
                p=p->next;
                {

                    p->prev->next=p->next;
                    p->next->prev=p->prev;

                }
                if(p!=NULL&&p->next!=NULL)
                {
                    p->prev->next=p->prev;


                }
                if(p!=NULL&&p->next!=NULL)

                }



        }


        front_insert(head);
        dispaly(head);

    }




    return 0;
}