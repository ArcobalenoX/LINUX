#include "myhead.h"

int jpeg_show(char * const path);
int bmp_show(unsigned char * jpg_buf,unsigned int width,unsigned int height);

int main(int argc,char **argv)
{

    if(argc != 2)
    {

        fprintf(stderr, "usage: %s  <xxx.jpg>\n",argv[0]);
        exit(-1);
    }


    jpeg_show(argv[1]);

    return 0;
}//end of te main



struct my_error_mgr
{
    struct jpeg_error_mgr pub;

    jmp_buf setjmp_buffer;
};
typedef struct my_error_mgr * my_error_ptr;

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
    my_error_ptr myerr = (my_error_ptr) cinfo->err;

    (*cinfo->err->output_message) (cinfo);

    longjmp(myerr->setjmp_buffer, 1);
}


int jpeg_show(char * const path)
{

    //1. 申请 解压用的对象
    struct jpeg_decompress_struct cinfo;

    struct my_error_mgr jerr; //出错处理对象

    //2.  准备好 jpeg 图片数据
    FILE * infile;		/* 文件流指针 */
    JSAMPARRAY buffer;		/* 存放行图片信息 */
    int row_stride;		/* 行宽 ，每一行像素点的字节数*/


    if ((infile = fopen(path, "rb")) == NULL)
    {
        fprintf(stderr, "can't open %s\n", path);
        return 0;
    }

    //3. 绑定出错处理对象
    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = my_error_exit;

    if (setjmp(jerr.setjmp_buffer))  //检查是否绑定失败
    {

        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
        return 0;
    }

    //4. 把图片 与解压对象进行绑定
    jpeg_create_decompress(&cinfo);//做解压准备（申请空间）

    jpeg_stdio_src(&cinfo, infile); //绑定图片


    //5. 读取图片的头信息
    jpeg_read_header(&cinfo, TRUE);


    //6. 1开始解压
    (void) jpeg_start_decompress(&cinfo);

    /* JSAMPLEs per row in output buffer */
    row_stride = cinfo.output_width * cinfo.output_components;
    /* Make a one-row-high sample array that will go away when done with image */
    buffer = (*cinfo.mem->alloc_sarray)
             ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);


    //6.2 申请缓冲区 存放 整个图片的 像素信息
    unsigned char * jpg_buf = Calloc(row_stride * cinfo.output_height, 1);

    printf("width:%d  height:%d\n",cinfo.output_width, cinfo.output_height);

    //7. 按行读取  cinfo.output_scanline--》读取的行数 从0开始
    while (cinfo.output_scanline < cinfo.output_height)
    {

        (void) jpeg_read_scanlines(&cinfo, buffer, 1); //读取一行的数据出来，放到buffer

        // put_scanline_someplace(buffer[0], row_stride); //显示这一行的数据
        memcpy(jpg_buf + (cinfo.output_scanline -1) * row_stride,\
               buffer[0], row_stride);
    }


    //8 . 把像素信息显示到 LCD 屏
    bmp_show(jpg_buf,cinfo.output_width,cinfo.output_height);




    //9. 结束解压 并释放 资源
    (void) jpeg_finish_decompress(&cinfo);

    jpeg_destroy_decompress(&cinfo);


    fclose(infile);




    return 1;

}


int bmp_show(unsigned char * jpg_buf,unsigned int width,unsigned int height)
{

    int fd  = Open("/dev/fb0", O_RDWR);

    unsigned char * fp = mmap(NULL,
                              800*480*4,
                              PROT_READ|PROT_WRITE,
                              MAP_SHARED,
                              fd,
                              0 );

    int i,j;
    for(j=0; j<height && j<480; j++)
    {
        for(i=0; i<width && i<800; i++)
        {
			//jpeg为RGB(012)  6818LCD 为BGR(210)
            fp[j*800*4 + i*4 + 0] = jpg_buf[j*width*3 + i*3 + 2];
            fp[j*800*4 + i*4 + 1] = jpg_buf[j*width*3 + i*3 + 1];
            fp[j*800*4 + i*4 + 2] = jpg_buf[j*width*3 + i*3 + 0];
        }

    }
    close(fd);
    munmap(fp,800*480*4 );
	return 0;

}





