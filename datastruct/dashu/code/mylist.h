#ifndef __MYLIST_H
#define __MYLIST_H


/**
	@File name : mylist.h
	@Author    : YDF
	@Contact   : 1483465133@qq.com
	@Date      : 2019-03-24
	@Vision    : V1.0
	@brief     : 关于大位数四则运算 链表头文件

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

/*********Packgage function myheader****/
#include "Package.h"

typedef struct _node
{
    int num;

    struct _node *next, *prev;
} Node, *PNode;


PNode list_init(void)
{

    PNode head = (PNode)Calloc(1, sizeof(Node));
    head->next = head->prev = head;
    head->num = 0; //用来存放元素个数
    return head;
}


PNode list_add(PNode head, PNode new)
{

    new->next = head->next;
    new->prev = head;

    head->next->prev = new;
    head->next = new;

    head->num++;
}

PNode list_add_tail(PNode head, PNode new)
{

    new->prev = head->prev;
    new->next = head;

    head->prev->next = new;
    head->prev = new;

    head->num++;
}

PNode list_pri(PNode head)
{

    PNode tmp;

    for(tmp= head->next; tmp!=head; tmp = tmp->next)
    {

        printf("%04d ",tmp->num);
    }
    puts("");
}

PNode list_pri_tail(PNode head)
{

    PNode tmp;

    for(tmp= head->prev; tmp!=head; tmp = tmp->prev)
    {

        printf("%04d ",tmp->num);
    }
    puts("");
}


PNode list_free(PNode head)
{


    head->prev->next = NULL;

    PNode tmp1,tmp2;

    for(tmp1 = head, tmp2 = tmp1->next; tmp2 != NULL; tmp1 = tmp2, tmp2=tmp2->next)
    {


        free(tmp1);
    }

    free(tmp1);
}

/**
	字符串倒序转换
**/
void strconver(char *tmp)
{

    int len = strlen(tmp);

    int i;
    char t;
    for(i=0; i<len/2; i++)
    {
        t = tmp[i];
        tmp[i] = tmp[len-i-1];
        tmp[len-i-1] = t;
    }
}


/**
	把输入到字符串转换成 链表元素
	每4位为一个元素， 高位在链表之后，低位在链表之前
**/
PNode MkList(char *tmp)
{

    PNode head = list_init();

    int len = strlen(tmp);

    strconver(tmp);

    int i,d;
    if(len%4 == 0)
    {
        d = 0;
    }
    else if(len%4 > 0)
    {
        d = 1;
    }

    char num[5] = {0};
    for(i=0; i< len/4 + d; i++)
    {

        memset(num,0,5);
        strncpy(num, tmp+i*4, 4);
        strconver(num);

        PNode new;
        new = (PNode)Calloc(1, sizeof(Node));
        new->num = atoi(num);
        list_add_tail(head, new);
    }

    return head;
}


/**
	把两条链表做加法运算， 并把结果保存在较大的数字的链表当中
	（一般认为元素个数最多的一条链表为较大的一方，如果相等，则默认head[0]链表为被加数）
**/
int ListAdd(PNode head[2])
{

    int i1=0,i2=0;

    //设置加数 和 被加数 的标识位 head[i1]-->被加数  head[i2]-->加数
    //printf("head[0]->num = %d  head[1]->num = %d\n",head[0]->num,head[1]->num);

    if(head[0]->num >= head[1]->num)
    {
        i1 = 0;
        i2 = 1;
    }
    else
    {
        i1 = 1;
        i2 = 0;
    }

    //printf("i1:%d  i2:%d\n",i1,i2);
    int n;        //循环控制
    int flag = 0; //保存进位
    PNode tmp1,tmp2;

    //以下for循环为依次把每个元素做加法运算（一般只需根据最小数字链表的元素个数来控制循环次数）
    tmp1 = head[i1]->next;
    tmp2 = head[i2]->next;

    for(n=0; n<head[i2]->num; n++) //加的次数 和 加数元素个数相等
    {

        printf("和: %d + %d + (进位:%d) = ",tmp1->num,tmp2->num,flag);

        tmp1->num = (tmp1->num + tmp2->num + flag);
        if( tmp1->num /10000 == 1)
        {
            flag = 1;
            tmp1->num = tmp1->num % 10000;
        }
        else
        {
            flag = 0;
        }

        printf("%d\n",tmp1->num);

        //注意:当for循环退出时， tmp1的指针已经移向了下一个没有做过加法的元素
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;

    }

    if(flag == 1)
    {

        //加完进位后 ，做循环判断（防止出现循环进位的情况）
        //例如： 9999 9999 9999 + 0001 -->要循环进位三次，并为链表增加一个新元素用来保存进位
        for(; tmp1 != head[i1]; tmp1 = tmp1->next)
        {

            if(flag == 1)
            {
                tmp1->num += flag;
                flag = 0;
            }
            else if(flag == 0)
            {
                break;
            }

            if(tmp1->num == 10000)
            {
                tmp1->num %= 10000;
                flag = 1;
            }
        }

        //防止最高为元素为 9999 加完进位后 还有进位--》必须增加新元素来保存进位
        if((tmp1 == head[i1]) && (flag == 1))
        {

            PNode new = (PNode)Calloc(1,sizeof(Node));
            new->num = 1;

            list_add_tail(head[i1],new);
        }
    }


    //返回被加数的 链表标记
    return i1;

}



void ListMul(PNode head[2])
{

    int i1,i2;

    if(head[0]->num >= head[1]->num)
    {
        i1 = 0;
        i2 = 1;
    }
    else
    {
        i1 = 1;
        i2 = 0;
    }

    PNode tmp1,tmp2;

    tmp1 = head[i1]->next; //指向被乘数
    tmp2 = head[i2]->next; //指向乘数

    PNode head_new[(head[i2]->num)];
    int n,m;
    int flag=0; //保存进位
    PNode tmp; //创建新链表的元素添加

    for(n=0; n< head[i2]->num ; n++)
    {

        printf("\n创建第 %d 条链表时的相乘过程：\n", n+1);
        head_new[n] = list_init();

        for(m=0; m < head[i1]->num; m++ )
        {
            tmp = (PNode)Calloc(1, sizeof(Node));
            printf("积：%d * %d + (进位:%d) = ",tmp2->num, tmp1->num, flag);
            tmp->num = tmp2->num * tmp1->num + flag;


            flag = 0;

            if(tmp->num >= 10000)
            {
                flag  = tmp->num / 10000;
                tmp->num %= 10000;
            }
            printf("%d\n",tmp->num);
            list_add_tail(head_new[n], tmp);

            tmp1 = tmp1->next;
        }

        if(flag > 0)
        {
            tmp = (PNode)Calloc(1, sizeof(Node));
            tmp->num = flag;
            flag = 0;

            list_add_tail(head_new[n], tmp);
        }

        tmp2 = tmp2->next;

        //给被乘数放大10000倍
        tmp = (PNode)Calloc(1, sizeof(Node));
        tmp->num = 0;
        list_add(head[i1],tmp);
        tmp1 = head[i1]->next;

    }



    //链表的相加
    PNode head_add[2];
    for(n=0,m=1; m<head[i2]->num; m++,n++)
    {

        head_add[0] = head_new[n];
        head_add[1] = head_new[m];
        printf("\nhead_new[%d] + head_new[%d]\n",n,m);
        int ret = ListAdd(head_add);
        list_free(head_new[n]);
    }

    if(head[i2]->num == 1)
    {
        m = 0;
        list_pri_tail(head_new[0]);
        list_free(head_new[0]);
    }
    else
    {

        list_pri_tail(head_new[m-1]);
        list_free(head_new[m-1]);
    }


    list_free(head[0]);
    list_free(head[1]);

}



int ListSub(PNode head[2])
{

    int i1=0,i2=0;

    //设置被减数 和 减数 的标识位 head[i1]-->被减数  head[i2]-->减数
    //printf("head[0]->num = %d  head[1]->num = %d\n",head[0]->num,head[1]->num);

    if(head[0]->num >= head[1]->num)
    {
        i1 = 0;
        i2 = 1;
    }
    else
    {
        i1 = 1;
        i2 = 0;
    }

    int n;        //循环控制
    int flag = 0; //保存退位
    PNode tmp1,tmp2;

    //以下for循环为依次把每个元素做减法运算（一般只需根据最小数字链表的元素个数来控制循环次数）
    tmp1 = head[i1]->next;
    tmp2 = head[i2]->next;

    for(n=0; n<head[i2]->num; n++) //减的次数 和 减数元素个数相等
    {

        printf("差: %d - %d - (退位:%d) = ",tmp1->num,tmp2->num,flag);
        tmp1->num = (tmp1->num - tmp2->num - flag);
        if( tmp1->num < 0)
        {
            tmp1->num = tmp1->num +10000 ;
            flag = 1;
        }
        else
        {
            flag = 0;
        }
        printf("%d\n",tmp1->num);

        //注意:当for循环退出时， tmp1的指针已经移向了下一个没有做过加法的元素
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;

    }

    if(flag == 1)
    {

        //加完进位后 ，做循环判断（防止出现循环进位的情况）
        //例如： 9999 9999 9999 + 0001 -->要循环进位三次，并为链表增加一个新元素用来保存进位
        for(; tmp1 != head[i1]; tmp1 = tmp1->next)
        {

            if(flag == 1)
            {
                tmp1->num -= flag;
                flag = 0;
            }
            else if(flag == 0)
            {
                break;
            }

            if(tmp1->num == 10000)
            {
                tmp1->num %= 10000;
                flag = 1;
            }
        }

    }


    //返回被减数的 链表标记
    return i1;

}

void ListDiv(PNode head[2])
{

    int i1,i2;

    if(head[0]->num >= head[1]->num)
    {
        puts("test");
        i1 = 0;
        i2 = 1;
    }
    else
    {
        puts("t2");
        i1 = 1;
        i2 = 0;
    }

    PNode tmp1,tmp2;

    tmp1 = head[i1]->next; //指向被乘数
    tmp2 = head[i2]->next; //指向乘数

    PNode head_new[(head[i2]->num)];
    int n,m;
    int flag=0; //保存进位
    PNode tmp; //创建新链表的元素添加

    for(n=0; n< head[i2]->num ; n++)
    {

        printf("\n\n创建第 %d 条链表时的 相乘过程：\n", n+1);
        head_new[n] = list_init();

        for(m=0; m < head[i1]->num; m++ )
        {
            tmp = (PNode)Calloc(1, sizeof(Node));
            printf("%d * %d + %d(flag) = ",tmp2->num, tmp1->num, flag);
            tmp->num = tmp2->num * tmp1->num + flag;
            printf("%d\n",tmp->num);

            flag = 0;

            if(tmp->num >= 10000)
            {
                flag  = tmp->num / 10000;
                tmp->num %= 10000;
            }

            list_add_tail(head_new[n], tmp);

            tmp1 = tmp1->next;
        }

        if(flag > 0)
        {
            tmp = (PNode)Calloc(1, sizeof(Node));
            tmp->num = flag;
            flag = 0;

            list_add_tail(head_new[n], tmp);
        }

        tmp2 = tmp2->next;

        //给被乘数放大10000倍
        tmp = (PNode)Calloc(1, sizeof(Node));
        tmp->num = 0;
        list_add(head[i1],tmp);
        tmp1 = head[i1]->next;

    }



    //链表的释放
    PNode head_add[2];
    for(n=0,m=1; m<head[i2]->num; m++,n++)
    {

        head_add[0] = head_new[n];
        head_add[1] = head_new[m];
        printf("head_new[%d] + head_new[%d]\n",n,m);
        int ret = ListAdd(head_add);

        printf("free head_new[%d]\n",n);
        list_free(head_new[n]);
    }

    if(head[i2]->num == 1)
    {
        m = 0;
        printf("pri head_new[%d]\n",m);
        list_pri_tail(head_new[0]);
        list_free(head_new[0]);
    }
    else
    {
        printf("pri head_new[%d]\n",m);
        list_pri_tail(head_new[m-1]);
        list_free(head_new[m-1]);
    }


    list_free(head[0]);
    list_free(head[1]);

}


#endif //end of __MYLIST_H

