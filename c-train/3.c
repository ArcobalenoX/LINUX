/********std header**********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>

/*
3、写一个函数，传入参数为应付钱数。返回值为买家最少付出的钱的张数
	int get MoneyNum(int  iInputMoney)
例如：买家应付351元，最少张数为5.备注：可支付的钱币只有100、50、10、5、1不考虑2、20以及小数部分。



*/
int money_number(int money,int money_deno[],int len,int numarr[]);
int money_number2(int money,int money_deno[][2],int len);

int main(int argc,char **argv)
{
	int money=0;
	printf("input money:");
	scanf("%d",&money);
	/*int money_deno[]={100,50,10,5,1};
	int numarr[]={0,0,0,0,0};

	printf("money number:%d\n",money_number(money,money_deno,5,numarr));
	for(int i=0;i<5;i++)
	{
		printf("%-4d-->%d张\n",money_deno[i],numarr[i]);
	}
	*/
	
	/*二维数组包含面额种类和每种面额的张数*/
	int money_deno[5][2]={100,0,50,0,10,0,5,0,1,0};
	
	printf("money number:%d张\n",money_number2(money,money_deno,5));
	for(int i=0;i<5;i++)
	{
		if(money_deno[i][1]!=0)
			printf("%-4d￥-->%2d张\n",money_deno[i][0],money_deno[i][1]);
	}	
	
	
	/*malloc指针测试*/
	char *ptr;
	if ((ptr = (char *)malloc(0)) == NULL)
		puts("Got a null pointer");
	else
		puts("Got a valid pointer");
	printf("%s\n",ptr);
	free(ptr);
	
		
	return 0;
}//end of te main



/******************************
	功能：
	参数：需要支付的金额，面额，面额种类，每种面额的数量
	返回：付出的最小钱数
	日期：2020.1.13
	版本：
	作者：


********************************/
int money_number(int money,int money_deno[],int len,int numarr[])
{
	int number=0;
	for(int i=0;i<len;i++)
	{
		number+=money/money_deno[i];
		numarr[i]=money/money_deno[i];
		//printf("%d\t-->%d张\n",money_deno[i],numarr[i]);
		money%=money_deno[i];
	}
	
	return number;
}



/******************************
	功能：
	参数：需要支付的金额，二维数组(面额，数量），面额种类
	返回：付出的最小钱数
	日期：2020.1.14
	版本：
	作者：


********************************/
int money_number2(int money,int money_deno[][2],int len)
{
	int number=0;
	for(int i=0;i<len;i++)
	{
		number+=money/money_deno[i][0];
		money_deno[i][1]=money/money_deno[i][0];
		//printf("%5d-->%3d张\n",money_deno[i][0],money_deno[i][1]);
		money%=money_deno[i][0];
	}
	
	return number;
}



