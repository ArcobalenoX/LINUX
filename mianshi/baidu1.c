#include<stdio.h>
#include<stdlib.h>
int main()
{
    int people_num=0;
    int juice_num=0;
    int i=0;
    int j=0;
    int t=0;
    int k=0;
    int sum=0;
    scanf("%d",&people_num);
    scanf("%d",&juice_num);

    int *plikej=(int*)malloc(sizeof(int)*people_num);
    int *paynum=(int*)malloc(sizeof(int)*juice_num);

    for(i=0; i<people_num; i++)
    {
        scanf("%d",&plikej[i]);
    }
    for(i=0; i<people_num; i++)
    {
        for(j=0; j<juice_num; j++)
        {
            if(plikej[i]==j+1)
                paynum[j]++;
        }
    }

    for(j=0; j<juice_num; j++)
    {
      
        sum+=paynum[j]/2+paynum[j]%2;
    }
  



    printf("%d\n",sum);


    free(paynum);
    free(plikej);
    return 0;
}