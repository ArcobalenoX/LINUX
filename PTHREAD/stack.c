#include <stdio.h>
#include <stdlib.h>

struct stack_data{
	int *stack;		//指针指向申请后的内存,(申请的栈空间的首地址)
	int top;		//申请后下标
};

int main()
{
	int n=5;//申请的栈空间大小
	
	struct stack_data *M = malloc(sizeof(struct stack_data));
	if(M !=NULL)
	{
		M->stack = malloc(sizeof(int)*n);
		if(M->stack==NULL)
			return -1;
		M->top = -1;
	}
	
	int num;
	scanf("%d",&num);
	
	//入栈操作
	while( num%8 != 0)
	{
		//判断是否满栈
		if(M->top == n-1)
		{
			printf("full stack\n");
			return -1;
		}
		
		//将余数放入到栈空间中(入栈)
		M->top++;
		M->stack[M->top] = num%8;
		num =num/8;
	}
	
	//出栈操作
	while(1)
	{
		//当数据出完以后,空栈退出
		if(M->top==-1)
			break;
		
		//将栈中的数据拿出来(出栈)
		printf("%d",M->stack[M->top]);
		M->top--;
	}
	printf("\n");
	
	return 0;
}





