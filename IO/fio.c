#include<stdio.h>
#include<strings.h>
#include<string.h>
int main(int argc,char*argv[])
{
	FILE *fpsrc=NULL;
	FILE *fpdest=NULL;
	int ret;
	fpsrc=fopen(argv[1],"r+");
	fpdest=fopen(argv[2],"w+");
	if(fpsrc==NULL||fpdest==NULL)
	{
		perror("fopen file");
		return -1;
	}
	printf("fileno----%d\n",fpsrc->_fileno);
	

	char buf[64];
	bzero(buf,64);
	/*
	ret=fread(buf,1,12,fpsrc);
	while(ret!=0 && feof(fpsrc)==0)
	{	
		fwrite(buf,1,12,fpdest);
		ret=fread(buf,1,12,fpsrc);
		
	}
	*/
	//printf("read ptr%s\n",fpsrc->_IO_read_ptr);
	//printf("%d\n",ret);
	
	
	fseek(fpsrc,0,SEEK_END);
	int total_num = ftell(fpsrc);  //文件位置指针当前位置相对于文件首的偏移字节数。
	printf("fseek ret = %d\n",ret);
	printf("total_num = %d\n",total_num);
	//fseek(fpsrc,0,SEEK_SET);	
	rewind(fpsrc);
	
	while(total_num > 0)
	{
		if(total_num >= 12)
		{
			fread(buf,1,12,fpsrc);
			fwrite(buf,1,12,fpdest);
			total_num -=12;
		}
		else
		{
			fread(buf,1,total_num,fpsrc);
			fwrite(buf,1,total_num,fpdest);
			total_num =0;
		}
	}
	
	fclose(fpsrc);
	fclose(fpdest);
	
	return 0;
}