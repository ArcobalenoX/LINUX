#ifndef __MYLIST_h_
#define __MYLIST_h_

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int num;
	struct node *next;
	
}NODE,*PNODE;

PNODE list_init(void)
{
	PNODE head=(PNODE)malloc(sizeof(NODE));
	head->next=NULL;
	return head;
}

void list_add_head(PNODE head,int n)
{
	if(head==NULL){puts("head is NULL");exit(-1);}
	PNODE node=(PNODE)malloc(sizeof(NODE));
	node->num=n;
	node->next=head->next;
	head->next=node;
	
	head->num++;

}

void list_add_tail(PNODE head,int n)
{
	if(head==NULL){puts("head is NULL");exit(-1);}
	
	PNODE node=(PNODE)malloc(sizeof(NODE)),tmp=head;
	node->num=n;
	
	while(tmp->next!=NULL)
		tmp=tmp->next;
	
	tmp->next=node;
	node->next=NULL;
	
	head->num++;
}


void list_pri(PNODE head)
{
	if(head==NULL){puts("head is NULL");exit(-1);}
	
	PNODE tmp ;
	for(tmp=head->next;tmp!=NULL;tmp=tmp->next)
		printf("%d  ",tmp->num);
	printf("\n");
	
}



void list_del(PNODE head,int n)
{
	if(head==NULL){puts("head is NULL");exit(-1);}
	
	PNODE tmp=head,p;
	while(tmp->next!=NULL)
	{
		if(tmp->next->num==n)
		{
			p=tmp->next;
			printf("del node %d\n",n);
			tmp->next=p->next;
			free(p);
		}
		else
			tmp=tmp->next;
		
	}
	
}


void list_free(PNODE head)
{
	if(head==NULL){puts("head is NULL");exit(-1);}
	
	PNODE tmp1=head,tmp2=tmp1->next;
	int i=0;
	for(;tmp1!=NULL;tmp2=tmp2->next)
	{
		printf("free node[%d] %d \n",i++,tmp1->num);
		free(tmp1);
		tmp1=tmp2;
		if(tmp1==NULL)break;
		
	}
	
}



#endif