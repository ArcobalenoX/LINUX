#include <stdio.h>
#include <stdlib.h>

typedef struct doublelist{
	int data;
	struct doublelist *next;
	struct doublelist *prev;
}*Doublelist;
//Doublelist 相当于 struct doublelist*

Doublelist create_doublelist(int num)
{
	Doublelist node = malloc(sizeof(struct doublelist));
	if(node ==NULL)
	{
		perror("malloc failed");
		return NULL;
	}
	node->data = num;
	node->next = NULL;
	node->prev = NULL;
}

void last_insert(Doublelist head)//尾部添加节点
{
	int i=0;
	Doublelist p;
	for(i=0;i<10;i++)
	{
		Doublelist new = create_doublelist(i);
		
		p=head;
		while(p->next != NULL)
			p=p->next;
		
		//尾部添加时,有两根线要链接(这里的线指指针赋值)
		p->next = new;
		new->prev = p;
	}
}

void front_insert(Doublelist head)//头部添加节点
{
	int i=0;
	for(i=0;i<10;i++)
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

void dispaly(Doublelist head)
{
	Doublelist p=head;
	while(p->next != NULL)
	{
		p=p->next;
		printf("---%d",p->data);
	}
	printf("\n");
}

int main()
{
	//创建头结点
	Doublelist head = create_doublelist(0);
	
	int num;
	while(1)
	{
		//输入数值
		scanf("%d",&num);
		
		if(num>0)//输入正数
		{
			Doublelist node = create_doublelist(num);
			
			//遍历节点,查找比num数值大的节点
			Doublelist p=head;
			while(p!=NULL)
			{
				p=p->next;
				if(p->data > num)
					break;
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
		
		else if(num<0)//输入负数
		{
			
			
			
			
			
		}
			
		
		
		
		
		
	}
	
	//尾部添加节点
	//last_insert(head);
	
	//头部添加节点
	front_insert(head);
	
	//正序打印
	dispaly(head);
	
	return 0;
}