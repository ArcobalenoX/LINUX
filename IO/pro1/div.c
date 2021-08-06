#include "fun.h"

int div(int a,int b)
{
	return a/b;
}

static int add(int a,int b)//这个函数只能被div.c调用
{
	return a*b;
}

int mul(int a,int b)
{
	int x = add(a,b);//执行的乘法
	return x;
}
