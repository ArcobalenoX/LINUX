#include <stdio.h>
#include <stdlib.h>

struct stack_data{
	int *stack;		//ָ��ָ���������ڴ�,(�����ջ�ռ���׵�ַ)
	int top;		//������±�
};

int main()
{
	int n=5;//�����ջ�ռ��С
	
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
	
	//��ջ����
	while( num%8 != 0)
	{
		//�ж��Ƿ���ջ
		if(M->top == n-1)
		{
			printf("full stack\n");
			return -1;
		}
		
		//���������뵽ջ�ռ���(��ջ)
		M->top++;
		M->stack[M->top] = num%8;
		num =num/8;
	}
	
	//��ջ����
	while(1)
	{
		//�����ݳ����Ժ�,��ջ�˳�
		if(M->top==-1)
			break;
		
		//��ջ�е������ó���(��ջ)
		printf("%d",M->stack[M->top]);
		M->top--;
	}
	printf("\n");
	
	return 0;
}





