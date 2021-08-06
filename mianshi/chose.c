#include<stdio.h>
#include<stdlib.h>
int main()
{
    int n=0;
    int i=0;
    int j=0;
    int t=0;
    int k=0;
    int sum=0;
	int time=0;
    scanf("%d",&n);
    int *p=(int*)malloc(sizeof(int)*n);
    int *a=(int*)malloc(sizeof(int)*n);
    int *b=(int*)malloc(sizeof(int)*n);
	
    for(i=0; i<n; i++)
    {
        scanf("%d",&p[i]);
		a[i]=p[i];
		b[i]=p[i];
    }

    for(i=0; i<n-1; i++)
    {
        k=i;
        for(j=i+1; j<n; j++)
            if(a[j]<a[k])
                k=j;
        if(k!=i)
        {
            t=a[k];
            a[k]=a[i];
            a[i]=t;
			time++;
        }
    }
	    for(i=0; i<n-1; i++)
    {
        k=i;
        for(j=i+1; j<n; j++)
            if(b[j]>b[k])
                k=j;
        if(k!=i)
        {
            t=b[k];
            b[k]=b[i];
            b[i]=t;
        }
    }
	
    for(i=0; i<n; i++)
    {
        printf("%d  ",a[i]);
    }
    printf("\n");
    for(i=0; i<n; i++)
    {
        printf("%d  ",b[i]);
    }
    printf("\n");

    for(i=0; i<n; i++)
    {
        t=a[i]-b[i];
        t=t>0?t:(-t);
        sum+=t;
    }
    printf("sum %d\n",sum);
   printf("time %d\n",time);
    free(p);
    return 0;
}