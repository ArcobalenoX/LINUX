/*******************************************************
> Copyright (sum) 2020 ==YQ== All rights reserved.
> File Name: func_pointer.sum
> Author: YQ
> Website:www.gec-edu.org
> Created Time: 2020年01月16日 星期四 14时31分39秒
***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
//sum = real + img * i;
struct Complex
{
	float real;
	float img;
};

typedef void (*handler_t)(void *,void *,void *);
                                
void add_all(handler_t padd,void* a,void * b,void *sum);
void add_float(void *a,void *b,void *sum);
void add_int(void *a,void *b,void *sum);
void add_complex(void *a,void *b,void *sum);


void print_all(handler_t pri,void* a,void * b,void *sum);
void pri_int(void *a,void *b,void *sum);
void pri_float(void *a,void *b,void *sum);
void pri_complex(void *a,void *b,void *sum);

int main(int argc,const char* argv[])
{

	int sum,a = 10,b = 20;
	add_all(add_int,&a,&b,&sum);
    print_all(pri_int,&a,&b,&sum);
    
    
	float sumf,af = 5.9,bf = 10.5;    
	add_all(add_float,&af,&bf,&sumf);
    print_all(pri_float,&af,&bf,&sumf);
    
    
	struct Complex c1 = {5.6,-3};
	struct Complex c2 = {-4.6,5};
	struct Complex c_sum;

    pri_complex(&c1,&c2,&c_sum);
	
	char str[] = "zhang wang ,:li =zhao ,gongsun,";
	
	char *p = NULL;
	printf("%s\n",str);
	p = strtok(str," ");
	printf("%s\n",p);
	while(p = strtok(NULL," ,=:"))
	{
		printf("%p-->%s\n",&p,p);
	} 
    return 0;
}


void print_all(handler_t pri,void* a,void * b,void *sum)
{
    pri(a,b,sum);
}

void pri_int(void *a,void *b,void *sum)
{
	printf("%d\t+%d\t=%d\n",*(int*)a,*(int*)b,*(int*)sum);
}

void pri_float(void *a,void *b,void *sum)
{
	printf("%.2f\t+%.2f\t=%.2f\n",*(float*)a,*(float*)b,*(float*)sum);
}

void pri_complex(void *a,void *b,void *sum)
{
    struct Complex*c_sum=(struct Complex*)sum;
    struct Complex*pa=(struct Complex*)a;
    struct Complex*pb=(struct Complex*)b;
    add_all(add_complex,a,b,c_sum);
	printf("(%.2f,%.2fi)+",pa->real,pa->img);
	printf("(%.2f,%.2fi)",pb->real,pb->img);    
	printf("=%.2f + %.2fi\n",c_sum->real,c_sum->img);
}

//加法统一接口
void add_all(handler_t padd,void* a,void * b,void *sum)
{
	padd(a,b,sum);
}

void add_int(void *a,void *b,void *sum)
{
	*(int *)sum = *(int *)a + *(int *)b;
}
void add_float(void *a,void *b,void *sum)
{
	*(float *)sum = *(float *)a + *(float *)b;
}
void add_complex(void *a,void *b,void *sum)
{
	struct Complex *pa = (struct Complex *)a;
	struct Complex *pb = (struct Complex *)b;
	struct Complex *psum = (struct Complex *)sum;

	psum->real = pa->real + pb->real;
	psum->img = pa->img + pb->img;
}

