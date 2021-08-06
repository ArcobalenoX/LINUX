#include<stdio.h>
void main()
{
	int n=0x12345678;
	char *t;
	t=(char*)&n;
	for(int i=0;i<4;i++)
	{
			printf("%p:%x\n",t,*t);
			t++;
	}




}
