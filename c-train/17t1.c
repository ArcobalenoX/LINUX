/*******************************************************
> Copyright (C) 2020 ==YQ== All rights reserved.
> File Name: str_sort.c
> Author: YQ
> Website:www.gec-edu.org
> Created Time: 2020年01月15日 星期三 11时31分36秒
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

int search_max_str(const char *s,char ch,int *max);
void sort(const char *s1,int len,char *s2);
void sort_array_2d(char (*ps)[],int row,int col);

int main(int argc,const char* argv[])
{
	char str[] = "   zhang wang li zhao gongsun";
	char new_str[sizeof(str)];
	
	memset(new_str,0,sizeof(new_str));

	sort(str,strlen(str),new_str);//函数调用

	printf("%s\n",new_str);
    return 0;
}
//函数定义
void sort(const char *s1,int len,char *s2)
{
	//子串分割(子串的个数，最长的子串大小,子串存储)
	int max = 0,count = 0;

	count = search_max_str(s1,' ',&max);

	printf("%d个子串，最长的子串:%d\n",count,max);

	char name[count][max + 1];
	memset(name,0,sizeof(name));

	char *p = NULL;

	int i = 0;

	char buf[strlen(s1) + 1];
	memset(buf,0,sizeof(buf));
	strcpy(buf,s1);

	p = strtok(buf," ");
	if(p != NULL)
	{
		strcpy(name[i],p);
		i++;
	}
	while(p = strtok(NULL," "))
	{
		strcpy(name[i],p);
		i++;
	}
	for(i = 0;i < count;i++)
	{
		printf("子串[%d]:%s\n",i,name[i]);
	}
	//排序

	sort_array_2d(name,count,max+1);
	//	name   <===> &name[0] =====> &buf
	//char name[][];
	//char buf[];
	/*
	char *pbuf = buf;
	char (*pname)[max+1] = &name[0];
	printf("%c\n",(*(pname + 0))[0]);
	printf("%c\n",(*(pname + 1))[0]);
	printf("%c\n",(*(pname + 2))[0]);
	*/
	//重组
	for(i = 0;i<count;i++)
	{
		strcat(s2,name[i]);
		strcat(s2," ");
	}
	return;
}
void sort_array_2d(char (*ps)[],int row,int col)
{
	printf("字符串排序:\n");
	int i,j;
	char (*p)[col] = (char (*)[col])ps; 
	char buf[col];
	for(i = 0;i<row-1;i++)
	{
		for(j = 0;j<row-1-i;j++)
		{
			if(strcmp(p[j],p[j+1]) > 0)
			{
				memset(buf,0,sizeof(buf));
				strcpy(buf,p[j]);
				strcpy(p[j],p[j+1]);
				strcpy(p[j+1],buf);
			}
		}
	}
	for(i = 0;i<row;i++)
	printf("%s\n",*( (char (*)[col])ps + i ));
}
/*
   函数功能:从一个指定字符串中，按指定的分割符，统计可以分割出的子串数目和最大字串的长度
*/
int search_max_str(const char *s,char ch,int *max)
{
	int count = 0;
	int n = 0;
    while(*s++ == ' ');
    s--;
	while(*s != '\0') //遍历字符串
	{
		if(*s != ch)//是不是分割符
		{
			n++;
		}
		else
		{
			if(n > *max)
			{
				*max = n;
			}
			n = 0;
			count++;
		}
		s++;//指向下一个字符的位置
	}
	if(*(s-1) == ch)
	{
		return count;
	}
	else
	{
		if(n > *max)
		{
			*max = n;
		}
		return ++count;
	}
}

