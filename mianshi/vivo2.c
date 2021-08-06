#include "stdio.h"
#include <stdlib.h>

/*
* Welcome to vivo !
*/

int getCountOfApp(const char* input)
{
    if(NULL == input)
    {
        return 0;
    }
    int cnt = 0;
    for(int i=0; input[i]!=0; ++i)
    {
        if(input[i] == ',')
        {
            ++cnt;
        }
    }
    return cnt/2;
}

//id start from 0
int getPositionOfApp(const char* input, const int id)
{
    int cntOfComma = id*2 + 1;
    int i=0;
    for(; input[i]!=0&&cntOfComma!=0; ++i)
    {
        if(input[i] == ',')
        {
            --cntOfComma;
        }
    }
    while(input[--i]!=' '&&input[i]!='#');
    return i+1;
}

#define APP_MAX 1000
#define DP_MAX 2048
int disks[APP_MAX];
int mems[APP_MAX];
int users[APP_MAX];
int dp[DP_MAX*DP_MAX];

int solution(int countOfApp, int disk, int mem)
{

    // TODO Write your code here
    int num=0;
    int i,j,k,m,n,t;

    for(i=0; i<2; i++)
    {
        for(j=0; j<2; j++)
        {
            for(k=0; k<2; k++)
            {
                for(t=0; t<2; t++)
                {
					
                    if((i*disks[0]+j*disks[1]+k*disks[2]+t*disks[3])<=disk
							&&(i*mems[0]+j*mems[1]+k*mems[2]+t*mems[3])<=mem)
                        n=i*users[0]+j*users[1]+k*users[2]+t*users[3];
						num=n>num?n:num;
                }

            }

        }



    }



    return num;
}

int main(int argc, char* args[])
{
    char input[10000];
    gets(input);
    const int countOfApp = getCountOfApp(input);
    if(0 == countOfApp)
    {
        return 0;
    }

    int disk = 0;
    int mem = 0;

    sscanf(input, "%d %d", &disk, &mem);
    for(int i=0; i< countOfApp; ++i)
    {
        const int pos = getPositionOfApp(input, i);
        sscanf(input+pos, "%d,%d,%d", &disks[i], &mems[i], &users[i]);
    }
    int num = solution(countOfApp, disk, mem);
    printf("%d\n", num);
    return 0;
}