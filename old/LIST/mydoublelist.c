#include<stdio.h>
#include<stdlib.h>
typedef struct doublelist
{
	int data;
	struct doublelist *next;
	struct doublelist *prev;
}*Doublelist;

Doublelist create_doublelist(int num)
{
	Doublelist node=malloc(sizeof(struct doublelist));
	if(node==NULL)
		perror("fail");
	node->data=num;
	node->next=NULL;	
	//node->next=node;
	node->prev=NULL;
	//node->prev=node;
	
}

void lastinsert(Doublelist head)
{
	int i=0;
	Doublelist p;
	for(i=0;i<10;i++)
	{
		Doublelist node=create_doublelist(i);
		
		p=head;
		while(p->next!=NULL)
			p=p->next;
		
		p->next=node;
		node->prev=p;
		
	}
		
}

void frontinsert(Doublelist head)
{
	int i;
	Doublelist p;
	for(i=0;i<10;i++)
	{
		Doublelist node=create_doublelist(i);
		
		if(head->next==NULL)
		{
			head->next=node;
			node->prev=head;
		}
		else
		{
			node->next=head->next;
			head->next=node;
			
			node->next->prev=node;
			node->prev=head;
			
		}
		
	}
	
}
void display(Doublelist head)
{
	Doublelist p=head;
	while(p->next!=NULL)
	{
		p=p->next;
		printf("-%d-",p->data);		
	}
	printf("\n");
	
}


int main()
{
	Doublelist head=create_doublelist(0);
	lastinsert(head);
	frontinsert(head);
	display(head);
	return 0;
}



