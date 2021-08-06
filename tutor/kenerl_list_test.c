#include <stdio.h>
#include "list.h"
#include <stdlib.h>

typedef struct link_list{
	int data;
	struct list_head k;
}*linknode;

linknode create_node(int num)
{
	linknode node = malloc(sizeof(struct link_list));
	if(node != NULL)
	{
		node->data=num;
		INIT_LIST_HEAD(&node->k);
	}
	
	return node;
}

int main()
{
	linknode head = create_node(0);
	if(head==NULL)
	{
		perror("head create failed\n");
		return -1;
	}
	
	int num;
	
	linknode p;
	struct list_head *pos,*n;
	int ret;
	while(1)
	{
		ret =scanf("%d",&num);
		if(ret == 0)
		{
			printf("input error\n");
			while(getchar()!='\n');
			continue;
		}
		
		if(num > 0)
		{
			linknode node = create_node(num);
			
			list_add_tail(&node->k,&head->k);
		}
		else if(num < 0)
		{
			list_for_each_safe(pos,n,&head->k)//等价于for循环
			{
				p = list_entry(pos,struct link_list,k);
				if(p->data + num == 0)
					list_del(&p->k);
			}
				
		}
		
		list_for_each(pos,&head->k)
		{
			p = list_entry(pos,struct link_list,k);
			printf("--%d--",p->data);
		}
		printf("\n");
	}
	
	return 0;
}
