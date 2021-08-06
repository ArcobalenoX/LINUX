#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc ,char *argv[])
{
	if(argc != 3)
	{
		perror("argc error");
		return -1;
	}
	char buf[24];
	int fdsrc = open(argv[1],O_RDONLY);
	int fddest = open(argv[2],O_RDWR|O_TRUNC|O_CREAT,0777);//覆盖
	//fddest = open(argv[2],O_RDWR|O_APPEND|O_CREAT,0777);//追加
	if(fdsrc ==-1||fddest==-1)
	{
		perror("open failed");
		return -1;
	}
	
	
	int size=lseek(fdsrc,0,SEEK_END);
	lseek(fdsrc,0,SEEK_SET);

	///**
	while((read(fdsrc,buf,24))!=0)
	{	
		write(fddest,buf,24);
	}
	
	//**/
	/*while(size > 0)
	{
		if(size > 24)
		{
			read(fdsrc,buf,24);
			write(fddest,buf,24);
			size -=24;

		}
		else
		{
			read(fdsrc,buf,size);
			write(fddest,buf,size);
			size = 0;
		}
	}
	*/
	printf("write success return \n");
	//lseek(fdsrc,0,SEEK_SET);
	
	close(fdsrc);
	close(fddest);
	return 0;
}