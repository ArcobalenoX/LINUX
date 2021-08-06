#include<stdio.h>
#include"fun.h"

int *p=NULL;
int *q=NULL;

int main()
{
	int num=0;
	while(scanf("%d",&num)!=1)
	{	
		printf("input not a num,input again \n");
		while(getchar()!='\n');
	}

	fun1(num);
	fun2(num);
			
	free(p);


	return 0;
}