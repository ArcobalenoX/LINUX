/*******************************************************
> Copyright (C) 2020 ==YQ== All rights reserved.
> File Name: bi_search.c
> Author: YQ
> Website:www.gec-edu.org
> Created Time: 2020年01月06日 星期一 17时09分01秒
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

void show_nums(int *nump,int n);
void sort_bubble(int *nump,int n);
int bi_serarch(int *nump,int len,int target);
int main(int argc,const char* argv[])
{
	srand(time(NULL));
	int total = 0;
	printf("Enter total:");
	scanf("%d",&total);

	int nums[total];
	int i;
	for(i = 0;i<total;i++)
	{
		nums[i] = random()%100;
	}
	show_nums(nums,total);
	sort_bubble(nums,total);
	show_nums(nums,total);

	int target = 0;
	printf("Enter target:");
	scanf("%d",&target);
	int pos;
	if(-1 == (pos = bi_serarch(nums,total,target)))
	{
		printf("%d 在数组中没有出现\n",target);
	}
	else
	{
		printf("%d 在数组中%d位置出现\n",target,pos);
	}
    return 0;
}
int bi_serarch(int *nump,int len,int target)
{
	int left = 0;
	int right = len -1;
	int middle;
	while(left <= right)
	{
		middle = (right + left)/2;
		if(nump[middle] == target)
		{
			return middle;
		}
		else if(nump[middle] > target)
		{
			left = middle + 1;
		}
		else if(nump[middle] < target)
		{
			right = middle;
		}
	}
	return -1;
}
void sort_bubble(int *nump,int n)
{
	int i,j,t;
	for(i = 0;i<n - 1;i++)
	{
		for(j = 0;j<n - 1 - i;j++)
		{
			if(nump[j] > nump[j+1])
			{
				t = nump[j];
				nump[j] = nump[j+1];
				nump[j+1] = t;
			}
		}
	}
}
void show_nums(int *nump,int n)
{
	int i;
	for(i = 0;i<n - 1;i++)
	{
		printf("%d ",nump[i]);
	}
	printf("%d\n",nump[i]);
}

