/**
	@File name : main.c
	@Author    : YDF
	@Contact   : 1483465133@qq.com
	@Date      : 2019-03-24
	@Vision    : V1.0
	@brief     : 关于大位数四则运算

**/

/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
#include <errno.h>
#include <stdarg.h>

#include "mylist.h"

void MkAdd(void);
void MkSub(void);
void MkMul(void);
void MkDiv(void);

int main(int argc,char **argv)
{

    int s;

    while(1)
    {

        system("clear");
        puts("          请选择相应的功能:");
        puts("          1.加法运算       ");
        puts("          2.减法运算       ");
        puts("          3.乘法运算       ");
        puts("          4.除法运算       ");
        puts("          5.退出       ");

        scanf("%d",&s);
        if(s==5)
        {
            break;
        }
        else switch(s)
            {

                case 1:
                    MkAdd();

                    break;
                case 2:
                    MkSub();

                    break;
                case 3:
                    MkMul();

                    break;
                case 4:
                    MkDiv();

                    break;
                default:

                    break;
            }

    }

    return 0;
}//end of te main



void MkAdd(void)
{

    int s;
    char tmp[100];
    PNode head[2];

    while(1)
    {
        puts("");
        puts("        请选择需要的功能:");
        puts("        1. 做加法运算    ");
        puts("        2. 退出          ");

        scanf("%d",&s);

        if(s<1 || s>2)
        {
            puts("输入有误，请重新输入");
            continue;
        }

        if(s == 1)
        {
            int i;
            for(i=0; i<2; i++)
            {

                memset(tmp, 0,100);
                printf("请输入第 %d 个数字:\n",i+1);
                scanf("%s",tmp);
                head[i] = MkList(tmp);
            }

            puts("num list 1:");
            list_pri(head[0]);
            puts("num list 2:");
            list_pri(head[1]);
            puts("\nresult:");

            i = ListAdd(head);
            list_pri_tail(head[i]);

            list_free(head[0]);
            list_free(head[1]);

        }
        else if(s == 2)
        {
            break;
        }
    }



}

void MkSub(void)
{

    int s;
    char tmp[100];
    PNode head[2];

    while(1)
    {
        puts("");
        puts("        请选择需要的功能:");
        puts("        1. 做减法运算    ");
        puts("        2. 退出          ");

        scanf("%d",&s);

        if(s<1 || s>2)
        {
            puts("输入有误，请重新输入");
            continue;
        }

        if(s == 1)
        {
            int i;
            printf("请输入大数减小数\n");
            for(i=0; i<2; i++)
            {

                memset(tmp, 0,100);
                printf("请输入第 %d 个数字:\n",i+1);
                scanf("%s",tmp);
                head[i] = MkList(tmp);
            }
            puts("num list 1:");
            list_pri(head[0]);
            puts("num list 2:");
            list_pri(head[1]);

            puts("\nresult:");
            i = ListSub(head);
            list_pri_tail(head[i]);

            list_free(head[0]);
            list_free(head[1]);

        }
        else if(s == 2)
        {
            break;
        }
    }



}


void MkMul(void)
{

    int s;
    char tmp[100];
    PNode head[2];

    while(1)
    {
        puts("");
        puts("        请选择需要的功能:");
        puts("        1. 做乘法运算    ");
        puts("        2. 退出          ");

        scanf("%d",&s);

        if(s<1 || s>2)
        {
            puts("输入有误，请重新输入");
            continue;
        }

        if(s == 1)
        {
            int i;
            for(i=0; i<2; i++)
            {

                memset(tmp, 0,100);
                printf("请输入第 %d 个数字:\n",i+1);
                scanf("%s",tmp);
                head[i] = MkList(tmp);
            }

            puts("num list 1:");
            list_pri_tail(head[0]);
            puts("num list 2:");
            list_pri_tail(head[1]);

            puts("\nresult:");
            ListMul(head);

        }
        else if(s == 2)
        {
            break;
        }
    }
}



void MkDiv(void)
{

    int s;
    char tmp[100];
    PNode head[2];

    while(1)
    {
        puts("");
        puts("        请选择需要的功能:");
        puts("        1. 做除法运算    ");
        puts("        2. 退出          ");

        scanf("%d",&s);

        if(s<1 || s>2)
        {
            puts("输入有误，请重新输入");
            continue;
        }

        if(s == 1)
        {
            int i;
            printf("请输入大数除以小数\n");
            for(i=0; i<2; i++)
            {

                memset(tmp, 0,100);
                printf("请输入第 %d 个数字:\n",i+1);
                scanf("%s",tmp);
                head[i] = MkList(tmp);
            }
            puts("num list 1:");
            list_pri_tail(head[0]);
            puts("num list 2:");
            list_pri_tail(head[1]);

            puts("\nresult:");
            ListDiv(head);

            list_free(head[0]);
            list_free(head[1]);

        }
        else if(s == 2)
        {
            break;
        }
    }



}