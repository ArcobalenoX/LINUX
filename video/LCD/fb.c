#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int frame_fd = open("/dev/fb0",O_RDWR);
	if(frame_fd==-1)
	{
		perror("open /dev/fb0 failed");
		return -1;
	}
	
	int color = 0xffffffff;
	// 透明度=0xff 红色=0xff 绿色=0xff 蓝色=0xff;
	
	int white = 0xff<<0 | 0xff <<8 | 0xff <<16	| 0xff <<24;
				//蓝色		绿色	  红色			透明度
	//在数值上，color和black相等
	
	int black = 0<<0    |  0x0 <<8 | 0x0  <<16 | 0x0 <<24;
	
	int red =  0<<0    |  0x0 <<8 | 0xff  <<16 | 0x0 <<24;
	
	int i;
	while(1)
	{
		for(i=0;i<800*480;i++)
			write(frame_fd,  &red ,4);
		sleep(1);
		lseek(frame_fd,0,SEEK_SET);//把文件光标偏移到文件开始的位置
		
		for(i=0;i<800*480;i++)
			write(frame_fd,  &black ,4);
		sleep(1);
		lseek(frame_fd,0,SEEK_SET);//把文件光标偏移到文件开始的位置
		
		for(i=0;i<800*480;i++)
			write(frame_fd,  &white ,4);
		sleep(1);
		lseek(frame_fd,0,SEEK_SET);//把文件光标偏移到文件开始的位置
	}
	

	close(frame_fd);
	
	return 0;
}