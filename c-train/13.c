/********std header**********/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <time.h>
#include <linux/mman.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>
#include <assert.h>
/*
 * 13、比较两字符串是否相同，并返回结果。
 * 
 */

char str_cmp(char s1[],char s2[])
{
    assert(s1!=NULL&&s2!=NULL);
    while(*s1++!='\0'&&*s2++!='\0')
    {
        
        if(*s1!=*s2)return *s1>*s2?'>':'<';
        
        //if(*s1<*s2)return '<';
        //    else if(*s1>*s2)return '>';
                   
    }
    return '=';
}

int main(int argc,char **argv)
{

    char str1[]="zhang";
    char str2[]="zhang?";
    printf("%s %c %s\n",str1,str_cmp(str1,str2),str2);
	return 0;
}//end of te main
