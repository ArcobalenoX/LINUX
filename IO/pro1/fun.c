#include "fun.h"


int flag;
static int add(int a,int b)//add函数只能被add.c调用
{
	return a+b;
}

int sub(int a,int b)
{
	int e=add(a,b);
	return e;
}


void func()
{
	flag++;
}