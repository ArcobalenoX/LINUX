#include<stdio.h>
#include<stdlib.h>
typedef struct _node{
	
	int id;
	struct _node *next;
}Node,*PNode;

void show(PNode head)
{
	PNode p=head,q;
	printf("%d  ",p->id);
	for(p=head->next;p!=head;p=p->next)
	{
		printf("%d  ",p->id);
	}

}
void main()
{
	
	PNode head =malloc(sizeof(Node));
	head->id = 1;
	head->next =head;
	int n=10;
	for(int i=n;i>1;i--)
	{
		PNode new =malloc(sizeof(Node));
		new->id = i;
		new->next = head ->next;
		head->next =new ;
		
		
	}
	
	show(head);
	PNode p=head,q;
	int k=n;
	int c=1;
	p=head;
	while(k>1)
	{
		if(c==2)
		{
			q=p->next;
			p->next=q->next;
			printf("\n%d出队\t剩余",q->id);
			
			free(q);
			show(p->next);
			c=0;
			k--;
		}
		c++;
		p=p->next;
	}
		printf("\n胜者%d\n",p->id);
	


}