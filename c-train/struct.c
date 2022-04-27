/********std header**********/
#define  _PG_std
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
#pragma pack(1)
typedef struct bock
{
    char a;
    short b;   

    int c;

    long d;
    float e;
    double f;


    unsigned int h:5;
    unsigned int m:6;
    unsigned int s:6;
    
}BOCK;
#pragma pack()
BOCK time_add(BOCK T1,BOCK T2);
int main(int argc,char **argv)
{
    BOCK t;
    t.h=16;
    t.m=30;
    t.s=30;
    printf("%p %ld\n",&t,sizeof(t));
    printf("long %ld\n",sizeof(long long int));
    printf("%p  %ld\n",&t.a,sizeof(t.a));
    printf("%p  %ld\n",&t.b,sizeof(t.b));
    printf("%p  %ld\n",&t.c,sizeof(t.c));
    printf("%p  %ld\n",&t.d,sizeof(t.d));
    printf("%p  %ld\n",&t.e,sizeof(t.e));
    printf("%p  %ld\n",&t.f,sizeof(t.f));   
    
    
    BOCK t2,t3;
    t2.h=13;
    t2.m=20;
    t2.s=40;
    t3=time_add(t,t2);
    printf("t3 %hd:%hd:%hd\n",t3.h,t3.m,t3.s);

    printf("offset %p\n",(&((BOCK*)0)->c));
    BOCK *tt= (BOCK*)((char*)&(t.c) - ((char*)(&((BOCK*)0)->c)));
    printf("tt %hd:%hd:%hd\n",tt->h,tt->m,tt->s);




    time_t timep;
    time(&timep);
    printf("%s\n",ctime(&timep));
	return 0;
}//end of te main

BOCK time_add(BOCK T1,BOCK T2)
{
    BOCK RET;
    unsigned int seconds=0;
    seconds=T1.h*3600+T1.m*60+T1.s;
    seconds+=T2.h*3600+T2.m*60+T2.s;
    
    RET.h=(seconds/3600)%24;
    RET.m=(seconds/60)%60;
    RET.s=(seconds)%60;
        
    return RET;
}


