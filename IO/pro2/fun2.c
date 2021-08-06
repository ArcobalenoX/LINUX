#include"fun.h"

void fun2(int num)
{
	int time =0;
	int *k=p;
	while(k!=q)
	{
		if(num%(*k)==0)
		{
			time++;
			printf("*%d",*k);
			num = num/ *k;
			continue;
		}
		k++;
	}
	if(time==0)
		printf("\n");
	else
		printf("\t%d个因式\n",time);
	
	
}