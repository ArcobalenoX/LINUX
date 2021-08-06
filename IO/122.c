#include<stdio.h>
#include "122.h"




int main()
{
	printf("%s %s \n",__TIME__,__DATE__);
	
	
#ifdef A 
	printf("DEFINE A = %d\n",A);
#else 
	printf("NO DEFINE A\n");
#endif	
	
	return 0;
}