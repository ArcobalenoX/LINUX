#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc ,char *argv[])
{
	char buf[]="123456789";
	int fd = open(argv[1],O_RDWR|O_TRUNC|O_CREAT,0777);
	if(fd==-1)
	{
		perror("creat failed");
		return -1;
	}
	write(fd,buf,strlen(buf));
	close(fd);
	return 0;
}