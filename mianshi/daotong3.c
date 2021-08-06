#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>



int main(int argc,char **argv)
{
    int i,j,k,goal;
    int city[7][7]= {0};
    scanf("%d",&goal);
    if(goal<0||goal>6)
    {
        printf("999\n");
        return 0;
    }
    for(i=0; i<7; i++)
    {
        for(j=0; j<7; j++)
        {
            scanf("%d,",&city[i][j]);

        }
    }

    for(i=0; i<7; i++)
    {
        for(j=0; j<7; j++)
        {
            printf("%d",city[i][j]);
            if(city[i][j]!=0||city[i][j]!=1)
            {
                printf("999\n");
                return 0;
            }
            if(city[i][j]!=city[j][i])
            {
                printf("999\n");
                return 0;
            }

        }
        printf("\n");
    }


    return 0;
}


