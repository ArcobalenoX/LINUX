#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>




/*
2、输入一个整数将每一位上的奇数放在一个新整数中，高位放在高位，低位在低位。

*/
int fun(int n)
{
    int out=0,i=n,j=0;
    for(;i>0;i=i/10)
    {
        j=i%10;
        if(j/2!=0)
            out=out*10+j;
       	else
	
    }    

    return out;
}


int main(int argc,const char* argv[])
{
	int n=0;
	printf("输入一个整数：\n");
	scanf("%d",&n);
	printf("%d\n",fun(n));
    

    return 0;
}


