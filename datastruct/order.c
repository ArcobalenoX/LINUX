/**

	@file name:顺序表的相关使用
	输入输出，添加删除
	由小到大排序（冒泡，选择，插入）

	@date:2019.3.2

	@version:
	@modify history:



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

int NUM = 10;

typedef struct NODE
{
    int *p;
    int n;

} *PNODE;

void tail_add(PNODE list,int data)//尾插
{

    if(list->n > NUM)
    {
        list->p=realloc(list->p,(NUM+=5)*sizeof(int));

    }

    list->p[list->n++]=data;


}

void head_add(PNODE list,int data)//头插
{
    if(list->n > NUM)
    {
        NUM+=5;
        list->p=realloc(list->p,(NUM)*sizeof(int));

    }


    for(int i=list->n; i>0; i--)
    {
        list->p[i]=list->p[i-1];
    }

    list->p[0]=data;
    list->n+=1;
}

void loc_add(PNODE list,int loc,int data)//指定位置插入
{
    if(list->n > NUM )
    {
        list->p=(int*)realloc(list->p,(NUM+=5)*sizeof(int));
    }

    if(loc >list->n)
    {
        list->n=loc;
        list->p=(int*)realloc(list->p,(NUM+=loc)*sizeof(int));

    }

    int i;
    for(i=list->n; i>loc; i--)
    {
        list->p[i]=list->p[i-1];
    }
    list->p[loc]=data;
    list->n+=1;

}


void show (PNODE list)
{
    int i;
    for(i=0; i < list->n; i++)
    {
        printf("p[%d]--%d\n",i,list->p[i]);
    }


}
void del(PNODE list,int data)
{
    int i,j;
    for(i=0; i<list->n; i++)
    {
        if(list->p[i]==data)
        {
            for(j=i; j<list->n; j++)
            {
                list->p[j]=list->p[j+1];
            }
            list->n-=1;
        }
    }

}

void sort(PNODE list)//冒泡排序
{
    int i,j,t,m=0;

    for(i=0; i < list->n; i++)
    {
        for(j=i+1; j < list->n; j++)
        {
            if(list->p[i]>list->p[j])//前一个大于后一个
            {
                t=list->p[i];
                list->p[i]=list->p[j];
                list->p[j]=t;
                m++;
            }

        }

        // printf("\n第%d躺比较\n",i+1);
        //  show(list);

    }


    /*
        for ( i = 0; i < list->n - 1; i++)
        {
            for (j = 0; j < list->n - 1 - i; j++)
            {
                if (list->p[j] > list->p[j+1])          // 相邻元素两两对比
                {
                    t = list->p[j+1];        // 元素交换
                    list->p[j+1] = list->p[j];
                    list->p[j] = t;
                    m++;
                }

            }
        }
    */

    printf("\n交换次数%d\n",m);

}

void sort2(PNODE list)//选择排序
{
    int i,j,t,m;
    for(i=0; i < list->n; i++)
    {
        m=i;//保存最小元素的下标
        for(j=i+1; j < list->n; j++)
        {
            if(list->p[j] < list->p[m])
            {
                m=j;
            }

        }

        if(m!=i)
        {
            t=list->p[i];
            list->p[i]=list->p[m];
            list->p[m]=t;
        }
        printf("\n第%d躺比较\n",i+1);
        show(list);
    }
}

void sort3(PNODE list)//插入排序
{
    int i,j,k,tmp;

    for(k=1; k<list->n; k++)//k(list->p[k])为待排序的元素
    {

        for(i=0; i<k; i++)//k与k之前的元素比较
        {
            if(list->p[k] < list->p[i])//k插入i的前面
            {
                tmp=list->p[k];//临时保存k

                for(j=k; j>i; j--)//后移
                {
                    list->p[j] = list->p[j-1];
                }

                list->p[i]=tmp;
            }

        }
        printf("\n第%d躺比较\n",k);
        show(list);
    }

}

int main(int argc,char **argv)
{
    struct  NODE list;
    list.n=0;
    list.p=(int*)calloc(NUM,sizeof(int));
    int t,l;
    for(int i=0; i<5; i++)
    {

        scanf("%d",&t);
        tail_add(&list,t);
        //loc_add(&list,i,t);
    }

    /*
    for(int i=0; i<5; i++)
	{

		scanf("%d",&t);
		head_add(&list,t);
		//loc_add(&list,i,t);
	}
    */

    show(&list);
    /*
        printf("input what del\n");
        scanf("%d",&t);
        del(&list,t);
    */

    /*    printf("bubble sort\n");
        sort(&list);
        show(&list);
    */

    /*    printf("input where add\n");
        scanf("%d%d",&l,&t);
        loc_add(&list,l,t);
        loc_add(&list,10,22);
        loc_add(&list,15,33);
        // loc_add(&list,20,44);
    	  show(&list);
    */


    /*    printf("select sort\n");
    	sort2(&list);
        show(&list);
    */
	
	
    sort3(&list);
    show(&list);


    free(list.p);
    return 0;
}//end of te main


