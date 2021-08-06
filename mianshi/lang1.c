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
    scanf("%d",&n);
    int *p=(int*)malloc(sizeof(int)*n);
    int *a=(int*)malloc(sizeof(int)*n);

    for(i=0; i<n; i++)
    {
        scanf("%d",&p[i]);
		a[i]=p[i];

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
        }
    }

    for(i=0; i<n; i++)
    {
        printf("%d  ",a[i]);
    }
    printf("\n");
	
	sum=(a[n-1]-a[0]) *(n-1);

    printf("%d\n",sum);

    free(p);
    return 0;
}