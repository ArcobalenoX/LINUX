#include "bmp_show.h"


void bmp_show(char *path_name, int x0, int y0){

	//1. 打开LCD的设备驱动文件 + mmap镜像fb0（LCD）
	int fd_lcd  = open("/dev/fb0", O_RDWR);
	if(fd_lcd == -1){
		perror("open fb0");
		exit(-1);
	}

	unsigned char * fb = (unsigned char *)mmap(NULL,//让内核自己制定映射地址
						   800*480*4,//映射大小 分辨率：800*480 每个像素点4个字节 BGRN BGRN ... ...)
						   PROT_READ|PROT_WRITE,//映射页到权限 读和写
						   MAP_SHARED, //共享
						   fd_lcd,
						   0);

	if(fb == NULL){
		printf("mmap err\n");
		exit(-1);
	}
	
	//2. 打开bmp图片--》读取像素
	int fd_bmp = open(path_name, O_RDONLY);
	if(fd_bmp == -1){
		fprintf(stderr,"open %s err\n", path_name);
		exit(-1);
	}
	/**
		bmp格式：54个头信息--》bmp的大小 分辨率  相关的时间信息
			 
			 后面剩余的像素信息 BGR BGR BGR ... ...
			 第一行像素点在最后一行存储， 最后一行在第一行存储， 整个是y镜像的
	**/
	int width,height;

	lseek(fd_bmp, 18, SEEK_SET);
	read(fd_bmp, &width, 4);
	read(fd_bmp, &height, 4);
	//printf("widht:%d  height:%d\n", width, height);

	int lm=0;
	if(width%4){
		lm = 4 - (width*3)%4;
		printf("off:%d\n", lm);
	}


	lseek(fd_bmp, 54, SEEK_SET);

	unsigned char * bmp_buf = (unsigned char *)calloc(1, 800*480*3);
	read(fd_bmp, bmp_buf, 800*480*3 );

	//3. 显示图片
	int i, j;
	int lcd_offset, bmp_offset;

	for(j=y0; j<480 && j<height+y0; j++){
		for(i=x0; i<800 && i<width+x0; i++){
		
			lcd_offset = ( i + j*800 ) * 4;
			bmp_offset = ( ( i - x0 ) + ( height - 1 - ( j - y0 ) ) * width ) * 3 + ( height-1-j + y0)*lm ;

			memcpy(fb + lcd_offset , bmp_buf + bmp_offset , 3);
		}
		
		
	}

	//4. 回收资源
	close(fd_lcd);
	close(fd_bmp);
	free(bmp_buf);
	munmap(fb,800*480*4);

	return;
}

void bmp_show_bck(char *path_name, int x0, int y0){

	//1. 打开LCD的设备驱动文件 + mmap镜像fb0（LCD）
	int fd_lcd  = open("/dev/fb0", O_RDWR);
	if(fd_lcd == -1){
		perror("open fb0");
		exit(-1);
	}

	unsigned char * fb = (unsigned char *)mmap(NULL,//让内核自己制定映射地址
						   800*480*4,//映射大小 分辨率：800*480 每个像素点4个字节 BGRN BGRN ... ...)
						   PROT_READ|PROT_WRITE,//映射页到权限 读和写
						   MAP_SHARED, //共享
						   fd_lcd,
						   0);

	if(fb == NULL){
		printf("mmap err\n");
		exit(-1);
	}
	
	//2. 打开bmp图片--》读取像素
	int fd_bmp = open(path_name, O_RDONLY);
	if(fd_bmp == -1){
		fprintf(stderr,"open %s err\n", path_name);
		exit(-1);
	}
	/**
		bmp格式：54个头信息--》bmp的大小 分辨率  相关的时间信息
			 
			 后面剩余的像素信息 BGR BGR BGR ... ...
			 第一行像素点在最后一行存储， 最后一行在第一行存储， 整个是y镜像的
	**/
	int width,height;

	lseek(fd_bmp, 18, SEEK_SET);
	read(fd_bmp, &width, 4);
	read(fd_bmp, &height, 4);

	if((width!=800) || (height != 480)){
		perror("show bck err");
		exit(-1);
	}


	lseek(fd_bmp, 54, SEEK_SET);

	unsigned char * bmp_buf = (unsigned char *)calloc(1, 800*480*3);
	read(fd_bmp, bmp_buf, 800*480*3 );

	//3. 显示图片
	int i, j;
	int lcd_offset, bmp_offset;

	for(j=y0; j<480 && j< y0+20 ; j++){
		for(i=x0; i<800 && i< x0+20 ; i++){
		
			lcd_offset = ( i + j*800 ) * 4;
			bmp_offset = ( i + ( height - 1 - j ) * width ) * 3 ;

			memcpy(fb + lcd_offset , bmp_buf + bmp_offset , 3);
		}
		
		
	}

	//4. 回收资源
	close(fd_lcd);
	close(fd_bmp);
	free(bmp_buf);
	munmap(fb,800*480*4);

	return;
}



#ifdef main

int main(int argc,char **argv)
{
	//./bmp_show ./1.bmp
	if(argc != 4){
		printf("usage: %s <path/xxx.bmp> <x0> <y0>\n",argv[0]);
		exit(-1);
	}

	int x0, y0;
	
	x0  = atoi(argv[2]);
	if(x0 < 0 || x0 >= 800){
	
		printf("0<=x<800");
		exit(-1);
	}
	
	y0  = atoi(argv[3]);
	if(y0 < 0 || y0 >= 480){
	
		printf("0<=y<800");
		exit(-1);
	}

	bmp_show(argv[1], x0 , y0);



	return 0;
}//end of te main

#endif



