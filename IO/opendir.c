#include <stdio.h>
#include <sys/types.h>
#include<dirent.h>

int main(int argc,char *argv[])
{
	//打开目录
	DIR *fp =  opendir(argv[1]);
	if(fp == NULL)
	{
		perror("opendir failed");
		return -1;
	}
	
	//读取目录
	struct dirent *dp;
	while((dp=readdir(fp))!=NULL)
	{
		printf("dp->d_ino=[%ld]\n",dp->d_ino);
		printf("dp->d_off=[%ld]\n",dp->d_off);
		printf("dp->d_reclen=[%d]\n",dp->d_reclen);
		printf("dp->d_type=[%d]\n",dp->d_type);	
		printf("dp->d_name=[%s]\n",dp->d_name);
		printf("=================\n");
	}
	
	//关闭目录
	closedir(fp);
	
	return 0;
}