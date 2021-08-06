#include <stdio.h>
#include <stdlib.h>


typedef struct stack_data{
	int *stack;
	int top;
}*stack_data;
int main()
{
	int n=5;
	int num;
	scanf("%d",&num);
	printf("%d",num);
	
	
	stack_data M = malloc(sizeof(struct stack_data));
	
	if(M!=NULL)	
	{	
		M->stack=malloc(sizeof(int)*n);
		if(M->stack!=NULL)
		M->top=-1;		
	}
	
	while(num%8!=0)
	{	
		if(M->top==(n-1)) 
			break;
		M->top++;
		M->stack[M->top]=num%8;
		num =num/8;
		printf("%d",num);
	}
			
	while(1)
	{
		if(M->top!=-1)
		{	
		printf("%d",M->stack[M->top]);
		(M->top)--;
		}
	}
	printf("\n");
	
	return 0;
}