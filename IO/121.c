#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct  students
{
	int age;
	char name[10];
	float score;
	
}A,B,C;

typedef struct  teachers
{	
	char name[10];
	int age;
}TS,*TSP;

union TST
{
	unsigned int num;
	short n[2];
	double x;
	char d[12];
	
};
enum	M
{
	red,
	yellow,
	blue,
	purple=7,
	black,
	white,
};
int main(int argc,char * argv[])
{
	
	struct students A={.age=12,.name="aaa",.score=66.6};//栈空间（8M）
	strcpy(B.name,"bbb");
	struct students *p=(struct students *)malloc(sizeof(struct students));//堆空间
	if(p==NULL)
		return -1;
	else 
		{
			p->age=18;
			strcpy(p->name,"one");
		}
	TS T[5]={"ttt",44,"rrr",55};

	TSP T2=(TSP)malloc(sizeof(TS));
	if(T2==NULL)
		return -1;
	else 
		{
			T2->age=18;
			strcpy(T2->name,"tbn");
		}
	printf("A.name =%s\n",A.name);	
	printf("B.age = %d\n",B.age);
	printf("T1.name =%s\n",T[0].name);	
	printf("T1.age = %d\n",T[0].age);
	printf("T2.name =%s\n",T2->name);	
	printf("T2.age = %d\n",T2->age);
	
	union TST	Z;
	printf("%lu\n",sizeof(Z));
	
	Z.num=0x12345678;	
	printf("ahal=%x\n",Z.num);
	unsigned int al=Z.n[0];
	unsigned int ah=Z.n[1];
	printf("al=%x\n",al);
	printf("ah=%x\n",ah);
	
	
	printf("red=%d\n",red);
	printf("white=%d\n",white);
	
		
	return 0;
}