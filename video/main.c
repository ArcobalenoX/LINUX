
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



int main(int argc,char **argv)
{
    system("./camera.out 50001 192.168.11.111 50000 &");

    char cmd[30];
    while(1)
    {
        memset(cmd,0,50);
        scanf("%s",cmd);
        if(strncmp(cmd,"exit",4)==0)
        {
            system("killall -12 camera.out");
            break;


        }
        else if(strncmp(cmd,"cap",3)==0)
        {
            system("killall -10 camera.out");

        }
		else if(strncmp(cmd,"show",4)==0)
		{
			system("./jpeg_show.out newphoto.jpg");			
		}



    }

    return 0;
}//end of te main


