#include<stdio.h>
#include<math.h>

#define swap(x,y) (x)=(x)+(y);(y)=(x)-(y);(x)=(x)-(y);//交换两个数
/*//所有小于等于N且不被7整除或者含7的正整数平方和
1、一个正整数，如果它能被7整除，或者它的十进制表示法中某个位数上的数字为7，则称其为与
7相关的数。求所有小于等于N的与7无关的正整数的平方和。
例如：N = 8，<= 8与7无关的数包括：1 2 3 4 5 6 8，平方和为：155。
*/
int fun(int n)
{
	int sum=0;
	int i=0;
	int j=0;
	int len=0;
	int tem=n;
	int flag=0;
	int m=0;
	while(tem>0)
	{
		len++;
		tem=tem/10;
	}
	printf("len-->%d\n",len);
	
	for(i=n;i>0;i--)
	{
		if(i%7==0)
		{
			//printf("i-->%d\n",i);
			continue;	
		}
		for(m=0;m<=len;m++)
		{
			j=pow(10,m);
			if((i/j)%10==7)
			{	
				flag=1;
				break;
			}
		}
		
		if(flag==1)
		{
			flag=0;
			//printf("i-->%d\n",i);
			continue;		
		}
		printf("i-->%d\n",i);
		sum+=(i*i);				
	}

	return sum;
}

int main(void)
{

	int n=0,sum=0;
	scanf("%d",&n);
	printf("%d\n",fun(n));
	
}
