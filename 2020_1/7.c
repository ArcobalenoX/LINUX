
/********std header**********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <time.h>
#include <linux/mman.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>

/*qsort 比较回调*/
int comp(const void *p1,const void *p2)
{
	/*if(*(int*)p1<*(int*)p2)return -1;
	else if(*(int*)p1>*(int*)p2)return 1;
	else return 0;*/
	return (*(int*)p1-*(int*)p2);
}

/*数组初始化*/
void arr_init(int arr[],int len)
{
    int i;
	for(i=0;i<len;i++)
	{
		arr[i]=random()%100;		
	}
	
}

/*打印数组*/
void show_arr(int arr[],int len)
{
	for(int i=0;i<len;i++)
	{
		printf("%d  ",arr[i]);
	}
	printf("\n");

}
/*

7、输入一串数，将其最小的放在第一位，次小的放在最后一位，再小的放在第二位，
   再再小的放在倒数第二位，以此类推。
*/
void fun(int arr[],int newarr[],int len)
{
	int i=0,j=0;
	for(;i<len/2;i++,j++)
	{
		newarr[j]=arr[2*i];
	
		newarr[len-1-j]=arr[2*i+1];
	}
		
	newarr[len/2]=arr[len-1];

}


int main(int argc,char **argv)
{
	srand(time(NULL));
	int n=0;

	printf("输入数组长度：");
	scanf("%d",&n);
	int arr[n];

	arr_init(arr,n);
    show_arr(arr,n);
    
	qsort(arr,n,sizeof(int),comp);
	show_arr(arr,n);
	

	int newarr[n];
	fun(arr,newarr,n);
	show_arr(newarr,n);

	return 0;
}//end of te main


