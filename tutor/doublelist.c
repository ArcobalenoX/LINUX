#include <stdio.h>
#include <stdlib.h>

typedef struct doublelist{
	int data;
	struct doublelist *next;
	struct doublelist *prev;
}*Doublelist;
//Doublelist �൱�� struct doublelist*

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

void last_insert(Doublelist head)//β����ӽڵ�
{
	int i=0;
	Doublelist p;
	for(i=0;i<10;i++)
	{
		Doublelist new = create_doublelist(i);
		
		p=head;
		while(p->next != NULL)
			p=p->next;
		
		//β�����ʱ,��������Ҫ����(�������ָָ�븳ֵ)
		p->next = new;
		new->prev = p;
	}
}

void front_insert(Doublelist head)//ͷ����ӽڵ�
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
			//next������
			new->next = head->next;
			head->next = new;
			//prev������
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
	//����ͷ���
	Doublelist head = create_doublelist(0);
	
	int num;
	while(1)
	{
		//������ֵ
		scanf("%d",&num);
		
		if(num>0)//��������
		{
			Doublelist node = create_doublelist(num);
			
			//�����ڵ�,���ұ�num��ֵ��Ľڵ�
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
				//�ٴα�������
				p=head;
				while(p->next != NULL)
					p=p->next;
		
				p->next = node;
				node->prev = p;
			}
		}
		
		else if(num<0)//���븺��
		{
			
			
			
			
			
		}
			
		
		
		
		
		
	}
	
	//β����ӽڵ�
	//last_insert(head);
	
	//ͷ����ӽڵ�
	front_insert(head);
	
	//�����ӡ
	dispaly(head);
	
	return 0;
}