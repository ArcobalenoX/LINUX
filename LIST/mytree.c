#include<stdio.h>
#include<stdlib.h>

typedef struct tree{
	int data;
	struct tree *left;
	struct tree *right;
}*TREE;

//创建节点
TREE creat_node(int num)
{
	TREE node=malloc(sizeof(struct tree));
	
	if(node!=NULL)
	{	
		node->data=num;
		node->left=NULL;
		node->right=NULL;
	}
	return node;
}

//插入节点
void insert(TREE root,TREE node)
{
	if(root->data > node->data)
	{
		if(root->left ==NULL)
			root->left =node;
		else 
			insert(root->left,node);
	}	
	
	else if(root->data < node->data)
	{
		
		if(root->right ==NULL)
			root->right =node;
		else
			insert(root->right,node);
	}
	
	
}


//先序遍历
void display_left(TREE root)
{
	printf("%d--",root->data);	

	if(root->left !=NULL)
	{
		display_left(root->left);
	}
	
	if(root->right!=NULL)
	{
		display_left(root->right);
	}

}

//中序遍历
void display_m(TREE root)
{
	if(root->left != NULL)
	{
		display_m(root->left);
	}
	printf("--%d",root->data);
	if(root->right !=NULL)
	{
		display_m(root->right);
	}
}

//后序遍历
void display_right(TREE root)
{
	if(root->right!=NULL)
	{
		display_right(root->right);
	}

	if(root->left !=NULL)
	{
		display_right(root->left);
	}
	
	printf("%d--",root->data);	
	
}

//队列
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

//入队
void quene_in(TREE root)
{
	if(num>0)
	{
		struct que_link *node = create_que_link(root->data);
		
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

}
//出队
void quene_out()
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

//按层遍历
void display_


int main()
{
	
	TREE root=creat_node(100);
	int i, num[6]={95,97,105,102,107,106};
	for(i=0;i<6;i++)
	{
		TREE node =creat_node(num[i]);
		insert(root,node);
	}
	display_left(root);
	printf("\n");
	display_m(root);
	printf("\n");
	display_right(root);
	printf("\n");
	return 0;
	
}