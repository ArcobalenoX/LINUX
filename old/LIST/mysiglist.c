#include <stdio.h>
#include <stdlib.h>

//定义结构体
struct list{
	int data;
	struct list *next;
};

//创建结点
struct list * create_node(int num)
{
	struct list* node =malloc(sizeof(struct list));
	if(node==NULL)
	{
		perror("malloc failed");
		return NULL;
		
	}
	node->data=num;
	node->next=NULL;
	
	return node;
}


int main(){
	
	struct list* head=create_node(0);
	struct list *p;
	int i;
	
	for(i=1;i<10;i++)
	{	
		struct list *node =create_node(i);
		p=head;
		while(p->next!=NULL)
			p=p->next;
				
		p->next=node;

	}
	
	p=head;
	while(p->next!=NULL)
	{
		printf(" %d---",p->data);
		p=p->next;
		
	}
	printf("\n");
	
	return 0;
}