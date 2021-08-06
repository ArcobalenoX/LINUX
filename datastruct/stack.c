/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>

#define SType int

typedef struct stack
{
    SType data;
    struct stack* next;

} SS,*PStack;


PStack stack_init(void)
{
    PStack p=calloc(1,sizeof(SS));
    p->next=NULL;

    return p;

}

void stack_push(PStack top,SType data)
{
    PStack new=stack_init();
    new->data=data;

    new->next=top->next;
    top->next=new;
}
SType stack_pop(PStack top)
{
    if(top->next == NULL)
    {
        printf("stack is empty\n");
        return (SType)-1;
    }
    SType ret=top->next->data;

    PStack tmp=top->next;
    top->next=tmp->next;

    free(tmp);
    return ret;
}

void stack_destroy(PStack top)
{

    PStack tmp1,tmp2;

    for(tmp1=top, tmp2 =top->next;  tmp2!=NULL;  \
            tmp1=tmp2, tmp2=tmp2->next)
    {
        free(tmp1);
    }

    free(tmp1);
}


int main(int argc,char **argv)
{
    PStack top=stack_init();
    int i,j=0;
    double num=0,k=0;
	puts("输入五位二进制");
    for(i=0; i<5; i++)
    {
        scanf("%d",&j);
        stack_push(top,j);
    }
    while(1)
    {
        j=stack_pop(top);
        printf("pop--%d\n",j);
        num += j*(pow(2,k++));

        if(top->next ==NULL||j==-1)break;
    }
    printf("num--%.0f\n",num);
    stack_destroy(top);



    /*十进制转化八进制*/
    top=stack_init();
    int n=0,t=0;
    puts("\n输入十进制数");
    scanf("%d",&n);
    for(; n!=0;)
    {
        t=n%8;
        stack_push(top,t);
        n=n/8;
    }
	puts("转化八进制结果为");
    while(1)
    {
        t=stack_pop(top);
        printf("%d ",t);
        if(top->next ==NULL||j==-1)break;
    }
    puts("\n");
    stack_destroy(top);



    return 0;
}//end of te main


