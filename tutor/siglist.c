#include <stdio.h>
#include <stdlib.h>

//�����ڵ�ṹ��
struct list{
	int data;			//�������
	struct list *next;	//����ָ����һ���ڵ�
};

//����ڵ�ĺ���
struct list * create_node(int num)
{
	struct list *node = malloc(sizeof(struct list));
	if(node == NULL)
	{
		perror("malloc failed");
		return NULL;
	}
	//�ֱ�Խڵ�������Ա��ֵ
	node->data = num;
	node->next = NULL;
	
	return node;
}



int main()
{
	struct list *head=NULL;	//����ͷ�ڵ�
	
	//�������ӽڵ�
	int i;
	struct list *p;
	for(i=0;i<10;i++)
	{
		//����ڵ�
		struct list *node = create_node(i);
		
		p=head;
		
		//��һ���ڵ�����
		if(p==NULL)
			head=node;
			
		//�ڶ������Ժ�Ľڵ�
		else 
		{
			//���ϱ�������,������ѭ��ʱ,Pһ��ָ�����һ���ڵ�
			while(p->next!=NULL)
				p=p->next;
			
			p->next = node;
		}
		
	}
	p=head;
	while(p->next !=NULL)
	{
		printf(" %d---",p->data);
		p=p->next;
	}
	printf(" %d---",p->data);
	printf("\n");
	
	return 0;
}