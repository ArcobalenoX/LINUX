
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

/*
10、一组2n+1个元素的正整形数组，按升序排序，然后将小于中间数值的成员替换为中间的值。
    例如：1,2,3,4,5，输出为：3,3,3,4,5，原型：int fun(int arry[],int n,char*output){return 0;}

*/


int comp(const void *p1,const void *p2);
int fun(int arr[],int len,char output[1024]);
void arr_init(int arr[],int len);
void arr_print(int arr[],int len);

int main(int argc,char **argv)
{
	//srandom(time(NULL));//随机数种子
	int n=0;
	printf("输入奇数得到2N+1数组：");
	scanf("%d",&n);
	int arr[n];
	
	arr_init(arr,n);
    arr_print(arr,n);
	
	qsort(arr,n,sizeof(int),comp);//升序排序
	printf("排序后：\n");
	arr_print(arr,n);
    
    char output[1024]={0};
	printf("替换后:\n");
	fun(arr,n,output);
	//arr_print(arr,n);
    printf("%s\n",output);
    

	return 0;
}//end of te main



/*比较回调函数*/
int comp(const void *p1,const void *p2)
{
	/*if(*(int*)p1<*(int*)p2)return -1;
	else if(*(int*)p1>*(int*)p2)return 1;
	else return 0;*/
	return (*(int*)p1-*(int*)p2);
}
/*替换小于中间值的前一半数*/
int fun(int arr[],int len, char output[1024])
{
	qsort(arr,len,sizeof(int),comp);
	for(int i=0;i<len/2;i++)
	{
		arr[i]=arr[len/2];
	}
    for(int i=0;i<len;i++)
	{
        sprintf(output+strlen(output),"%d,",arr[i]);
	}
    output[strlen(output)-1]='\0';
	return 0;
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
void arr_print(int arr[],int len)
{
	for(int i=0;i<len;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");

}
