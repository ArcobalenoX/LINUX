/**单项链表**/


#include"commonheader.h"

#define SIZE 20
typedef int datatype;
typedef	struct node
{
    datatype data;
    struct node * next;

} listnode,*singly_list;

singly_list init_list(void)
{
    singly_list mylist = malloc(sizeof(listnode));
    if(mylist!=NULL)
    {
        mylist->next = NULL;
    }
    return mylist;

}

bool is_empty(singly_list list)
{
    return list->next == NULL;
}

singly_list new_node(datatype data,singly_list next)
{

    singly_list new = malloc(sizeof(listnode));
    if(new != NULL)
    {
        new->data = data;
        new->next = next;

    }

    return new;
}

void insert_node(singly_list head,singly_list new)
{
    if(head == NULL || new == NULL)
    {
        return;
    }
    new->next = head->next;
    head->next = new;

}
bool remove_node(singly_list mylist,singly_list delete)
{
    if( is_empty(mylist) )
        return false;
    singly_list p = mylist;
    while(p != NULL && p->next != delete)
    {
        p = p->next;
    }

    if(p == NULL)
        return false;
    p->next = delete->next;
    delete->next = NULL;

    return true;

}

void move_node(singly_list mylist,singly_list p,singly_list anchor)
{
    if(mylist == NULL || p == NULL || anchor == NULL);
    {
        return;

    }
    remove_node(mylist,p);
    insert_node(anchor,p);

}

void show(singly_list list)
{
    if( is_empty(list) )
        return;
    singly_list p = list->next;
    int i =0;
    while(p!=NULL)
    {
        printf("%s%d", i ==0 ? ("") : ("-->"),p->data);
        p=p->next;
        i++;

    }
    printf("\n");

}
singly_list find_node(singly_list mylist,datatype data)
{
    if( is_empty(mylist) )
        return NULL;
    singly_list p = mylist->next;

    while(p!=NULL)
    {
        if(p->data == data)
            break;
        p=p->next;


    }

    return p;

}


int parse(char buf[SIZE],int number[2])

{
    if(strcmp(buf,"\n")==0)
        return 0;
    int count = 1;
    char *p,delim[]=" ";
    p=strtok(buf,delim);
    number[0] = atoi(p);

    p=strtok(NULL,delim);
    if(p!=NULL)
    {
        number[1] = atoi(p);
        count++;

    }
    return count;


}


int main (void )
{





    return 0;
}













































































