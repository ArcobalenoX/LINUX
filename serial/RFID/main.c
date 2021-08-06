/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>

/**********IO header*************/
#define  _PG_IO
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

/*********Packgage function myheader****/
#include "Package.h"

#include "rfid.h"

int main(int argc,char **argv)
{
	unsigned cardid;

	while(1){
	
		if(!GetRfId(&cardid)){
			printf("---->id:%x\n", cardid);
		}
	
	}
	

	return 0;
}//end of te main


