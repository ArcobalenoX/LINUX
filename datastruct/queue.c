#include <stdio.h>
#include <stdlib.h>

struct que_link{
	int data;
	struct que_link *next;
};

struct head_link{
	int n;		//队列中节点的个数
	struct que_link *front;//始终指向将要被删除的节点
	struct que_link *last;//始终指向最新添加的节点
};

struct head_link *create_head_link()
{
	struct head_link *head = malloc(sizeof(struct head_link));
	if(head !=NULL)
	{
		head->n = 0;
		head->front = NULL;
		head->last = NULL;
	}
	return head;
}

struct que_link *create_que_link(int num)
{
	struct que_link *node = malloc(sizeof(struct que_link));
	if(node !=NULL)
	{
			node->data = num;
			node->next = NULL;
	}
	return node;
}

int main()
{
	struct head_link *head = create_head_link();
	if(head== NULL)
	{
		perror("create_head_link fialed");
		return -1;
	}
	
	int num;
	while(1)
	{
		scanf("%d",&num);
		//入队操作
		if(num>0)
		{
			struct que_link *node = create_que_link(num);
			
			//第一个数值入队
			if(head->n == 0)
			{
				head->last = node;
				head->front = node;
				head->n++;
			}
			else
			{
				head->last->next = node;
				head->last = node;
				head->n++;
			}
		}
		//出队
		else if(num<0)
		{
			if(head->n == 0)
			{
				printf("队列已空\n");
				continue;
			}
			else
			{
				//q指向将要出队的节点
				struct que_link *q = head->front;
				printf("%d出队\n",q->data);
				
				//将front指针指向下一个要被出队的节点
				head->front = head->front->next;
				head->n--;
				
				//释放空间
				free(q);
			}
		}
		else
			break;
		
		struct que_link *p = head->front;
		while(p!=NULL)
		{
			printf("--%d",p->data);
			p=p->next;
		}
		printf("\n");

	}
	
	return 0;
}



