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
#include <assert.h>
/*
 * 17、对姓氏进行排名
 * Char str[ ]=”zhang   wang   li    zhao”
 * Char str_ new[ ]=”li  wang   zhang   zhao”
 * 接口：sort（str,len,str_new）
 * 
 * 
 */

void search_max_num(char str[],char ch,int*max,int*num);
void str_sort(char (*str)[],int num,int max);
void sort(const char*s1,char ch,char*s2);
static int cmpstringp(const void *p1, const void *p2)
{
   return strcmp(* (char * const *) p1, * (char * const *) p2);
}

void sort2(const char*s1,char ch,char*s2);

int main(int argc,char **argv)
{
    //char str[]={"zhang wang li zhao deng fan zhou "};
    char str[]={"zhang wang=li,zhao:deng fan zhouzsio "}; 
    char newstr[sizeof(str)]={0};

    sort2(str,strlen(str),newstr);
    printf("%s\n",newstr);
    

	return 0;
}//end of te main




void search_max_num(char str[],char ch,int*max,int*num)
{
    int n=0;
    int count=0;
    int idx=0;
    while(str[idx++]==' ');//跳过开头空格
    idx--;
    while(str[idx]!='\0')
    {
        //printf("%c",str[idx]);
        if(str[idx]!=ch)
        {
            n++;
        }
        else
        {             
         
           *max=*max>n?*max:n;
             count++;
            n=0;
        }
        idx++;
    }
    
    if((str[idx-1])==ch) *num=count;//末尾空格
    else 
    {
        *num=count+1;
        *max=*max>n?*max:n;
    }
}


void str_sort(char (*str)[],int num,int max)
{

    char (*p)[max]=(char (*)[max])str;//数组指针强转，指向长度为max的数组
    char buf[max];
    
    for(int i=0;i<num-1;i++)
    {
        for(int j=0;j<num-1-i;j++)
        {
            if(strcmp(p[j],p[j+1])>0)
            {
                bzero(buf,max);
                strcpy(buf,p[j]);
                strcpy(p[j],p[j+1]);
                strcpy(p[j+1],buf);
            }
            
        }
        
    }

}
void sort(const char*s1,char ch,char*s2)
{
    int max=0;
    int num=0;
    char buf[strlen(s1)+1];
    strcpy(buf,s1);
    
    /*找子串数和最大长度*/
    search_max_num(buf,' ',&max,&num);
    printf("max:%d num:%d\n",max,num);
    printf("buf:%s\n",buf);
    
    /*子串提取*/
    char namearr[num][max+1];//二维数组，namearr为数组指针
    memset(namearr,0,sizeof(namearr));
    char *delim=" ";
    int i=0;
    char *p=strtok(buf,delim);
    if(p!=NULL)
    {
        strcpy(namearr[i++],p);
    }
    while(p=strtok(NULL,delim))
    {
        strcpy(namearr[i++],p);
    }
    for(int i = 0;i < num;i++)
	{
		printf("子串[%d]:%s\n",i,namearr[i]);
	}
    /*子串排序*/    
    str_sort(namearr,num,max+1);

	for(int i = 0;i<num;i++)
	{
		strcat(s2,namearr[i]);
		strcat(s2," ");
	}
}


void sort2(const char*s1,char ch,char*s2)
{
    int max=0;
    int num=0;
        printf("%d\n",sizeof(s1));    

    char buf[strlen(s1)+1];
    strcpy(buf,s1);
    /*找子串数和最大长度*/
    //search_max_num(buf,' ',&max,&num);
    //printf("max:%d num:%d\n",max,num);
    printf("s1 buf:%s\n",buf);    

    int n=0;
    char *delim=" ,:=";
    /*子串提取*/
    int namemaxnum=20;
    char *namearr[namemaxnum];//指针数组
    memset(namearr,0,sizeof(namearr));
    
    int i=0;//子串计数
    char *p=strtok(buf,delim);
    if(p!=NULL)
    {
        namearr[i]=p;
        printf("%s %ld\n",namearr[i],strlen(namearr[i]));
       
        max=strlen(namearr[i]);
        i++;
    }
    while(p=strtok(NULL,delim))
    {
        namearr[i]=p;
        printf("%s %ld\n",namearr[i],strlen(namearr[i]));
        n=strlen(namearr[i]);
        i++;
        max=n>max?n:max;
    }
    num=i;
    printf("max:%d num:%d\n",max,num);
   
    for(int i = 0;i < num;i++)
	{
		printf("原子串[%d]:%p-->%s\n",i,&namearr[i],namearr[i]);
	}

    /*排序*/
    qsort(namearr, num, sizeof(char *), cmpstringp);
    for(int i = 0;i<num;i++)
	{
        printf("新子串[%d]:%p-->%s\n",i,&namearr[i],namearr[i]);
        strcat(s2,namearr[i]);
		strcat(s2," ");
	}

}


