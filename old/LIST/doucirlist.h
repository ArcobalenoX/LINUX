#ifndef __DOUCIRLIST_h_
#define __DOUCIRLIST_h_

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int num;
	struct node *next;
	struct node *prev;
}NODE,*PNODE;

PNODE list_init(void)
{
	PNODE head=(PNODE)malloc(sizeof(NODE));
	head->next=head;
	head->prev=head;
	return head;
}

void list_add_head(PNODE head,int n)
{
	if(head==NULL){puts("head is NULL");exit(-1);}
	
	PNODE node=(PNODE)malloc(sizeof(NODE));
	node->num=n;
	
	
	node->next=head->next;
	node->prev=head;
	head->next->prev=node;
	head->next=node;
	
	
	head->num++;
}

void list_add_tail(PNODE head,int n)
{
	if(head==NULL){puts("head is NULL");exit(-1);}
	
	PNODE node=(PNODE)malloc(sizeof(NODE));
	node->num=n;
	
	node->prev=head->prev;
	node->next=head;
	head->prev->next=node;
	head->prev=node;
	head->num++;
}


void list_pri(PNODE head)
{
	if(head==NULL){puts("head is NULL");exit(-1);}
	
	PNODE tmp ;
	for(tmp=head->next;tmp!=head;tmp=tmp->next)
		printf("%d  ",tmp->num);
	printf("\n");
	
}



void list_del(PNODE head,int n)
{
	if(head==NULL){puts("head is NULL");exit(-1);}
	
	PNODE tmp=head;
	while(tmp->next!=head)
	{
		if(tmp->num==n)
		{
			printf("del node %d\n",n);
			tmp->prev->next=tmp->next;
			tmp->next->prev=tmp->prev;
			free(tmp);
		}
		else
			tmp=tmp->next;
		
	}
	head->num--;
}


void list_free(PNODE head)
{
	if(head==NULL){puts("head is NULL");exit(-1);}
	
	PNODE tmp1=head,tmp2=tmp1->next;
	int i=0;
	for(;tmp1->next!=head;tmp2=tmp2->next)
	{
		printf("free node[%d] %d \n",i++,tmp1->num);
		free(tmp1);
		tmp1=tmp2;
		if(tmp1==head)break;
	}
	free(head);
	
	
}

void list_addsmall(PNODE head,PNODE node)
{
	
	
	DST->num=SRC->num;
	for(tmp=head->next;tmp!=head;tmp=tmp->next)
		printf("%d  ",tmp->num);
	
}



#endif