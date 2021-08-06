#include <stdio.h>
#include <stdlib.h>

//链表节点结构体
struct list{
	int data;			//存放数据
	struct list *next;	//用来指向下一个节点
};

//申请节点的函数
struct list * create_node(int num)
{
	struct list *node = malloc(sizeof(struct list));
	if(node == NULL)
	{
		perror("malloc failed");
		return NULL;
	}
	//分别对节点两个成员赋值
	node->data = num;
	node->next = NULL;
	
	return node;
}



int main()
{
	//申请一段内存作为头结点
	struct list *head=create_node(0);	
	
	//链表添加节点
	int i;
	struct list *p;
	for(i=0;i<10;i++)
	{
		//申请节点
		struct list *node = create_node(i);
		
		p=head;

		//不断遍历链表,当跳出循环时,P一定指向最后一个节点
		while(p->next!=NULL)
			p=p->next;
		
		p->next = node;
	}
	p=head;
	while(p->next !=NULL)
	{
		p=p->next;
		printf(" %d---",p->data);
	}
	printf("\n");
	
	return 0;
}