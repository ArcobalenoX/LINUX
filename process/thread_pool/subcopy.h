#ifndef _SUBCOPY_H_
#define _SUBCOPY_H_

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <fcntl.h>
#include<sys/unistd.h>

int is_dir(char *path);
int endwith(char *s,char c);
char* str_contact(char *str1,char *str2);
void copyfile(char* source_path,char* destination_path);
//void copydir(char* source_path,char* destination_path);
void *copydir(void*arg);

typedef struct  src_dest
{
	char src[100];
	char dest[100];
	
}*src_dest;



#endif


