/********std header**********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>


/*
 * 提示用户输入日、月和年。月份可以是月份号、月份 名或月份名缩写。
    然后该程序应返回一年中到用户指定日子(包括这一天) 的总天数。
 */
typedef struct Date
{
    int nian;
    int yue;
    int ri;
    char yuefen[10];
    int days;
    
}DATE;
int day_count(DATE *date);
int get_mon(DATE *date);

int main(int argc,char **argv)
{
    DATE in_date;
    memset(&in_date,0,sizeof(in_date));
    printf("%d\n",sizeof(in_date));
    //printf("输入年月日：");
    //scanf("%d%d%d",&(in_date.nian),&(in_date.yue),&(in_date.ri));
    printf("输入年：");
    scanf("%d",&(in_date.nian));
    printf("输入月：");
    scanf("%s",(in_date.yuefen));
    printf("输入日：");
    scanf("%d",&(in_date.ri));
    if(get_mon(&in_date)==0)
        printf("月份错误\n");
    else
    {
        printf("%dyear %dmonth %dday\n",in_date.nian,in_date.yue,in_date.ri);
        day_count(&in_date);
        printf("天数:%d\n",(in_date.days));   
    }
	return 0;
}//end of te main
/*
   函数功能:计算从指定年份的1.1到当前日期的天数
   函数参数:当前日期结构体指针,DATE *
   函数返回值:整型，计算出的天数
*/
int day_count(DATE *date)
{
    int months[12]={31,28,31,30,31,30,31,30,31,30,31,30};
 
    int nian=date->nian;
    int yue=date->yue;
    int ri=date->ri;
    int days=0;
    int runnian=0;
    if((nian%4==0&&nian%100!=0)||nian%400==0)
        runnian=1;
        
    for(int i=0;i<yue-1;i++)
    {
        days+=months[i];
    }
    if(yue>2)
        days+=runnian;
    days+=ri;
    
    date->days=days;
    return days;
}
/*
   函数功能:从月份名计算第几月
   函数参数:当前日期结构体指针,DATE *
   函数返回值:第几月
*/
int get_mon(DATE *date)
{
    char mon[12][10]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};

    for(int i=0;i<12;i++)
    {
        if(!strncasecmp(mon[i],date->yuefen,3))
            {
                date->yue=i+1;
                return date->yue;
            }
    }
    return 0;
} 
