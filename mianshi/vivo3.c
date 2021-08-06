#include <stdio.h>
#include <string.h>  
#define MAX_SIZE 1000

/*
* Welcome to vivo !
*/

int solution(char* src) {
    int num = 0;

    // TODO Write your code here
	char *p=src;
	int i,j,k,t=0;
	
	for(i=0;i<strlen(src);i++)
	{
		if(*p=='0')
			k=i;
			p++;			
	}	
	p=src;
	p+=k;
	for(i=k;i<strlen(src);i++)
	{
		if(*p=='('||*p==')')
			t++;
			p++;			
	}
	num=t;
	t=0;
	for(i=k;i>=0;i--)
	{
		if(*p=='('||*p==')')
			t++;
			p--;			
	}
	if(t<num)
		num=t;
	
    return num;
}

int main() {
    char src[MAX_SIZE] = {0};
    int num = 0;
    scanf("%s", src); 
    num = solution(src);
    printf("%d\n", num);
    return 0;
}