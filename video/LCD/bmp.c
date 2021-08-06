#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

int main()
{
	int frame_fd = open("/dev/fb0",O_RDWR);
	if(frame_fd==-1)
	{
		perror("open /dev/fb0 failed");
		return -1;
	}
	
	//===================映射内存================
	int *fbmem = mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,
					MAP_SHARED,frame_fd,0);
	if(fbmem == MAP_FAILED)
	{
		perror("mmap failed");
		return -1;
	}
	

	//打开图片
	int bmp_fd = open("2.bmp",O_RDONLY);
	if(bmp_fd == -1)
	{
		perror("open 2.bmp failed");
		return -1;
	}
	
	//从打开的图片文件读取54字节头文件，此时文件光标开始指向RGB24
	char bmp_head[54];
	read(bmp_fd,bmp_head,54);
	
	//从图片中读取RGB24的数据
	char bmp_rgb[800*480*3];
	read(bmp_fd,bmp_rgb,800*480*3);
	
	//定义int类型的数组--->32位的数组
	int fb_rgb[800*480];
	
	int i;
	for(i=0;i<800*480;i++)
		fb_rgb[i]= bmp_rgb[3*i]<<0 |bmp_rgb[3*i+1]<<8|bmp_rgb[3*i+2]<<16;
		//fb_rgb[0] = bmp_rgb[0]<<0 |bmp_rgb[1]<<8|bmp_rgb[2]<<16;
		//fb_rgb[1] = bmp_rgb[3]<<0 |bmp_rgb[4]<<8|bmp_rgb[5]<<16;
		//fb_rgb[2] = bmp_rgb[6]<<0 |bmp_rgb[7]<<8|bmp_rgb[8]<<16;
	
	for(i=0;i<800*480;i++)
		*(fbmem+i)=fb_rgb[i];
	
	
	munmap(fbmem,800*480*4);
	close(frame_fd);
	
	return 0;
}