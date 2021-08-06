#include <stdio.h>
#define max(a,b) (a>b?a:b)
#define yearsecond (365*24*3600)

#define N 2
#define	M N+1
#define NUM (M+1)*M/2

void  main()
{
	int i=0;
	while(i<NUM)
	{
		printf("%d\n",i++);
	}

  
}
