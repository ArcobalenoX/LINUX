#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{

    int n=0,t=0;
	int sum=0;
    scanf("%d",&n);
    while(n!=0)
    {
        t=n%2;
		printf("%d ",t);
        if(t==1)
			sum++;
        n=n/2;
    }
    printf("%d\n",sum);
    return 0;
}

