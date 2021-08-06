/*******************************************************
> Copyright (C) 2020 ==YQ== All rights reserved.
> File Name: book_serach.c
> Author: YQ
> Website:www.gec-edu.org
> Created Time: 2020年01月18日 星期六 09时32分22秒
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct Book
{
	char book_name[128];//char *book_name;
	char author[64];
	float price;
	struct Book *next;
}BOOK;

char books[][128] = {"C语言程序设计","爵迹","三重门","平凡的世界","围城","红高梁","史记","白鹿原","繁星","我们仨"};
char authors[][32] = {"谭浩强","郭敬明","韩寒","路遥","钱钟书","莫言","陈忠实","司马迁","冰心","杨绛"};

BOOK *creat_linklist(int n);
void print_linklist(BOOK *head);
void assign_linklist(BOOK *head);

int main(int argc,const char* argv[])
{
//	printf("%ld\n",sizeof(BOOK));
	srand(time(NULL));
	printf("请输入书本的个数:\n");
	int n;
	scanf("%d",&n);

	BOOK *head = NULL;
	
	head = creat_linklist(n);
    printf("main:%p\n",head);
	assign_linklist(head);
	print_linklist(head);
	//链表释放
    return 0;
}
void print_linklist(BOOK *head)
{
	if(head == NULL)
	{
		return;
	}
	BOOK *tmp;
	for(tmp = head->next;tmp != NULL;tmp = tmp->next)
	{
		printf("%s,%s,%.1f\n",tmp->book_name,tmp->author,tmp->price);
	}
}
void assign_linklist(BOOK *head)
{
    printf("assign:%p\n",head);
	if(head == NULL)
	{
		return;
	}
	head = head->next;
	while(head != NULL)
	{
		strcpy(head->book_name,books[random()%10]);
		strcpy(head->author,authors[random()%10]);
		head->price = 20.0 + random()%100 * 0.1;
		head = head->next;
        printf("assign:%p\n",head);
	}
	/*
	for(;head != NULL;head = head->next)
	{

	}
	*/
}
/*
   函数功能:创建具有n个结点的链表
*/
BOOK *creat_linklist(int n)
{
	BOOK *book,*head,*new;
	head = book = (BOOK *)malloc(sizeof(BOOK));//头结点
	memset(book,0,sizeof(BOOK));
	
	int i;
	for(i = 0;i < n;i++)
	{
		if(NULL == (new = (BOOK *)malloc(sizeof(BOOK))))
		{
			perror("malloc");
			return head;
		}
		memset(new,0,sizeof(BOOK));
		book->next = new;
		book = book->next;
	}
	book->next = NULL;
	return head;
}

