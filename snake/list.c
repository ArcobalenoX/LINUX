#include "list.h"

PNode list_init(void)
{

    PNode head = (PNode)calloc(1, sizeof(Node));

    head->next = head->prev = head;

    return head;
}


void list_add_head(PNode head, PNode new)
{

    new->next = head->next;
    new->prev = head;

    head->next->prev = new;
    head->next = new;
}

void list_add_tail(PNode head, PNode new)
{

    new->prev = head->prev;
    new->next = head;

    head->prev->next = new;
    head->prev = new;
}



void list_del_tail(PNode head)
{

    if(head->prev == head)return;

    PNode tmp = head->prev;

    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;

    free(tmp);
}

void list_del(PNode head,int x,int y)
{
    if(head->prev == head)return;
    PNode tmp;
    for(tmp = head->next;tmp!=head; tmp = tmp->next)
    {
        if(tmp->x==x && tmp->y==y)
        {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            free(tmp);
        }
    }
}


void list_free(PNode head)
{

    PNode tmp1,tmp2;

    head->prev->next = NULL;

    for(tmp1 = head, tmp2 = tmp1->next; \
            tmp2 != NULL; tmp1 = tmp2, tmp2 = tmp2->next)
    {

        free(tmp1);
    }

    free(tmp1);
}









