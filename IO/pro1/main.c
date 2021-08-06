#include <stdio.h>
#include "fun.h"


int main()
{
	int a=1;
	int b=2;
	
	//int c = add(a,b);
	//printf("c=%d\n",c);
	
	int d = sub(a,b);
	printf("d=%d\n",d);
	
	printf("flag=%d\n",flag);
	func();
	printf("flag=%d\n",flag);
	
	int e = div(100,10);
	printf("e=%d\n",e);
	
	int f = mul(10,20);
	printf("f=%d\n",f);

	
	return 0;
}

