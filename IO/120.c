#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define DEF *(unsigned int * (0x12345678))
int add(int a,int b);
int sub(int a,int b);
int mul(int a,int b);
int div(int a,int b);
//int func(int a,int b,f(int,int));

void swap (int *p1,int *p2);
void swap2(int ** m, int** n);
void pr3();
void pr5();
void pr7();
void funcall();


int retmul(int y);
int retadd(int x);

void Hanoi(int n, char a,char b,char c);
void Move(int n, char a, char b);
int count;

void merge (char  *d, int size,char* s1,char* s2);



int max_same_char(char*s);
bool  is_match(char* s);
float funs(int n);

int main(int argc,char* argv[])
{
/*	int a,b;
	scanf("%d%d",&a,&b);
	printf("add=%d\n",add(a,b));
	printf("sub=%d\n",sub(a,b));
	printf("mul=%d\n",mul(a,b));
	printf("div=%d\n",div(a,b));
	
	
	char input[16]="abc,d,e";
    char*p;
    p=strtok(input,",");
    if(p)
        printf("%s\n",p);
        
    p=strtok(NULL,",");
    if(p)
        printf("%s\n",p);
	p=strstr(input,"d,e");
    if(p)
        printf("%s\n",p);
	
	int x=10,y;
	y=10*x++;
	printf("%d",y);
*/
	/*funcall(pr3);
	funcall(pr5);
	funcall(pr7);
	printf("%d\n",retmul(10));
	printf("%d\n",retadd(10));
	

	*/
	//Hanoi(4, 'A', 'B', 'C');
	
	//2.1
	// char  s1[]="Hello World!";
	// char  s2[]="Hello World!";
	// if( s1==s2 )
		// printf("Equal!");
	// else	
		// printf("Not equal!\n");
	// printf("s1=%x\n",s1);
	// printf("s2=%x\n",s2);
	
	//2.2
	// char  s[]="Hello World!";
	// char* p = s;
	// int n=10;
	// printf("%d %d %d %d\n",sizeof(s),sizeof(p),strlen(p),sizeof(n)); //13 4（64-8） 12 4
	
	//2.3
	// int a=1,b=2,*p=&a,*q=&b;
	// swap(p,q);
	// printf("%d,%d,%d,%d,",a,b,*p,*q);//2,1,2,1,

	// swap2(&p,&q);
	// printf("%d,%d,%d,%d\n",a,b,*p,*q);//	2,1,1,2
	
	//2.4	
	// char  s1[]="acmghn",s2[]="bcfhi",s3[20];
	// memset(s3,0,sizeof(s3));
	// merge(s3,sizeof(s3)-1,s1,s2);
	// puts(s3);//abccfhimghn
	
	
	
	char s[128]={0};
	printf("input char s\n");
	scanf("%s",s);
	
	printf("%d\n",max_same_char(s));
	is_match(s);	
	
	int n=11;
	printf("%f\n",funs(n));

	
	return 0;
	
}
int add(int a,int b)
{
	return a+b;
}

int sub(int a,int b)
{
	return a-b;
}

int mul(int a,int b)
{
	return a*b;
}

int div(int a,int b)
{
	return a/b;
}



typedef void (*fnc)();
void funcall(fnc ff)
{
	ff();
}

void pr3()
{
	int i;
	for(i=1;i<4;i++)
		printf("第%d次打印\n",i);
}

void pr5()
{
	int i;
	for(i=1;i<6;i++)
		printf("第%d次打印\n",i);
}

void pr7()
{
	int i;
	for(i=1;i<8;i++)
		printf("第%d次打印\n",i);
}


int retadd(int x)
{
	if(x==0)
		return 0;
	//return retmul(x)+retadd(x-1);
	return x+retadd(x-1);
}
int retmul(int y)
{	
	if(y==1)
		return 1;
	return y*retmul(y-1);			
}

void swap (int* p1,int* p2)
{ 
	int t ;
	int* p;
	t= *p1;
	*p1= *p2;
	*p2=t;
	
	p = p1;//形参交换
	p1=p2;
	p2 = p;
}
void swap2(int ** m, int** n)
{
	int* p;
	p=*m;
	*m =*n;
	*n = p;
} 


void merge (char  *d, int size,char* s1,char* s2)
{    
	while ( *s1 != 0  &&  *s2 != 0)
	{
		if  (*s1 < *s2)
			*d++ = *s1++;
		else
			*d++ = *s2++;
     }
	while ( *s1 != 0 )  *d++ = *s1++;
	while ( *s2 != 0 )  *d++ = *s2++;
	*d = 0;
}

void Hanoi(int n, char a, char b, char c)
{
    if (n == 1)
    {
        Move(n, a, c);
    }
    else
    {
        Hanoi(n - 1, a, c, b);
        Move(n, a, c);
        Hanoi(n - 1, b, a, c);
    }
}
void Move(int n, char a, char b)
{
    count++;
    printf("第%d次移动 Move %d: Move from %c to %c !\n",count,n,a,b);
}




int max_same_char(char*s)
{
	
	char*p=s,*q=s;
	int max=0,m=0;
	while(*p!='\0' )
	{
		if(*q==*p)
		{
			m++;
			p++;
			max=(max>m?max:m);
		}	
		else
		{
			m=0;
			q=p;	
		}
	}
	
	/*
	int num=1,max=0;
	while(*s!=0)
	{
		while(*s==*(s+1))
		{
			num++;
			s++;
			
		}
		s++;
		max=(max>num?max:num);
		num=1;
	}
	*/

	return max;
}
bool  is_match(char* s)
{
	char a[4]={0,0,0,0};

	
	while(*s!=0)
	{
		switch(*s++)
		{
			case '(':
					a[0]++;break;
			case ')':
					a[0]--;break;
			case '[':
					a[1]++;break;
			case ']':
					a[1]--;break;
			case '{':
					a[2]++;break;
			case '}':
					a[2]--;break;
			case '<':
					a[3]++;break;
			case '>':
					a[3]--;break;
			default:break;
		}
		if(a[0]<0||a[1]<0||a[2]<0||a[3]<0)
		{
			printf("fei fa\n");
			return false;
			break;
		}
		
	}
	
	if(a[0]==0&&a[1]==0&&a[2]==0&&a[3]==0)
		{
			printf("he fa\n");
			return true;
		}
	else if(a[0]>0 ||a[1]>0 ||a[2]>0 ||a[3]>0)
		{	
			printf("fei fa\n");
			return false;
		}
	
}
float funs(int n)
{
	float M=0,N=0;
	if(n==1)
		return 1;
	else
	{
		N=(1+n)*n/2;
		M=1/N;
		return funs(n-1)+M;		
	}

}
