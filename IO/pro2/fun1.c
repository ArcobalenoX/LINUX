#include"fun.h"

void fun1(int num)
{
	p=(int*)calloc(4,num);
	if(p==NULL)
	{
		perror("calloc failed");
		exit(-1);
	}
	q=p;
	
	int flag=1;
	int i;
	while(num >1)
	{
		flag=1;
		for(i=2;i<=num/2;i++)
		{
			if(num%i==0)
			{
				flag=0;
				break;
			}
		}	
		if(flag==1)			
		{
			*q++ = num ;
		}
		num--;
	}	
	
	int *k=p;
	while(*k!=*q)
	{
		printf("%d\t",*k);
		k++;
	}
	printf("\n");
}