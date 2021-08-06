#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int num;
pthread_rwlock_t m;//读写锁变量


//链表节点结构体
struct list{
	int data;			//存放数据
	struct list *next;	//用来指向下一个节点
};
//申请一段内存作为头结点
struct list *head;	
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
void addnode(struct list *head)
{
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
}

//遍历打印链表数据
void display(struct list *head)
{
	struct list *p=head;
	while(p->next !=NULL)
	{
		p=p->next;
		printf(" %d---",p->data);
	}
	printf("\n");
}

void dellist(struct list *head)
{
	int i;
	struct list *p;
	p=head;
	for(i=0;i<10;i++)
	{
		p->data=0;
		
		//不断遍历链表,当跳出循环时,P一定指向最后一个节点
		while(p->next!=NULL)
			p=p->next;
		
	}
	
	
}

void *func1()
{
	sleep(1);
	int i=0;
	pthread_rwlock_rdlock(&m);//加读锁
	//dellist(head);
	printf("func1\n");
	pthread_rwlock_unlock(&m);//解锁
}

void *func2()
{
	sleep(1);
	int i=0;
	pthread_rwlock_rdlock(&m);//加读锁
	sleep(1);
	printf("func2\n");
	pthread_rwlock_unlock(&m);//解锁
}

int main()
{

	
	pthread_rwlock_init(&m,NULL);
	
	pthread_t tid1;
	pthread_create(&tid1,NULL,func1,NULL);
	
	pthread_t tid2;
	pthread_create(&tid2,NULL,func2,NULL);
	
	pthread_rwlock_wrlock(&m);//加写锁
	
	head=create_node(0);	
	printf("123\n");
	addnode(head);
	display(head);
	
	
	
	pthread_rwlock_unlock(&m);//解锁
	printf("456\n");
	pthread_exit(NULL);
	

}