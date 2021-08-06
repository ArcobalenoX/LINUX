#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct kernel_list{
	int data;
	struct list_head list;
}*KL;

KL init_kernel_list()
{
	KL head=malloc(sizeof(struct kernel_list))
	if(head!=NULL)
		INIT_LIST_HEAD(&head->list);
	return head;
}


KL init_kernel_node(int num)
{
	KL node=malloc(sizeof(struct kernel_list));
	if(node!=NULL)
	{
		node->data=num;
		INIT_LIST_HEAD(&node->list)	;
	}
	return node;
}

/*void show_list(KL head)
{
	LH *pos;
	list_for_each(pos, &head->list) 
	{
		KL node=list_entry(pos,KL,list);
		printf("_&d_",node->data);	
	}
	putchar('\n');
	
}*/


int main()
{
	KL head=init_kernel_list(0);
	KL p;
	struct list_head *pos,*n;
	
	int num;
	while(1)
	{	
		ret=scanf("%d",&num)
		KL new =init_kernel_node(i);
		list_add(&new->list,&head->list);		
	}
	
	show_list(head);
	
	
	
	
	
	return 0;
}