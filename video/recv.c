
#include "yuyv.h"
#include "lcd.h"
#include "touch.h"

int iphonex;
struct sockaddr_in phoneaddr ;
struct sockaddr_in bindaddr;
int addrsize ;
static char cap_flag=0;//拍照控制
static char	conti_run=1;//运行控制


struct buffer
{
    void   *start;
    size_t length;
};


typedef struct
{

    struct jpeg_destination_mgr pub;
    JOCTET * buffer;
    unsigned char *outbuffer;
    int outbuffer_size;
    unsigned char *outbuffer_cursor;
    int *written;

} mjpg_destination_mgr;


typedef mjpg_destination_mgr *mjpg_dest_ptr;

static char *           dev_name        = "/dev/video7";
static int              fd              = -1;
struct buffer *         buffers         = NULL;
static unsigned int     n_buffers       = 0;
FILE *file_fd;
static unsigned long file_length;
static unsigned char *file_name;


METHODDEF(void) init_destination(j_compress_ptr cinfo)
{
    mjpg_dest_ptr dest = (mjpg_dest_ptr) cinfo->dest;
    dest->buffer = (JOCTET *)(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE, OUTPUT_BUF_SIZE * sizeof(JOCTET));
    *(dest->written) = 0;
    dest->pub.next_output_byte = dest->buffer;
    dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

}

METHODDEF(boolean) empty_output_buffer(j_compress_ptr cinfo)
{

    mjpg_dest_ptr dest = (mjpg_dest_ptr) cinfo->dest;
    memcpy(dest->outbuffer_cursor, dest->buffer, OUTPUT_BUF_SIZE);
    dest->outbuffer_cursor += OUTPUT_BUF_SIZE;
    *(dest->written) += OUTPUT_BUF_SIZE;
    dest->pub.next_output_byte = dest->buffer;
    dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

    return TRUE;

}

METHODDEF(void) term_destination(j_compress_ptr cinfo)
{
    mjpg_dest_ptr dest = (mjpg_dest_ptr) cinfo->dest;
    size_t datacount = OUTPUT_BUF_SIZE - dest->pub.free_in_buffer;
    /* Write any data remaining in the buffer */
    memcpy(dest->outbuffer_cursor, dest->buffer, datacount);
    dest->outbuffer_cursor += datacount;
    *(dest->written) += datacount;

}


void dest_buffer(j_compress_ptr cinfo, unsigned char *buffer, int size, int *written)
{
    mjpg_dest_ptr dest;
    if (cinfo->dest == NULL)
    {
        cinfo->dest = (struct jpeg_destination_mgr *)(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT, sizeof(mjpg_destination_mgr));
    }

    dest = (mjpg_dest_ptr)cinfo->dest;
    dest->pub.init_destination = init_destination;
    dest->pub.empty_output_buffer = empty_output_buffer;
    dest->pub.term_destination = term_destination;
    dest->outbuffer = buffer;
    dest->outbuffer_size = size;
    dest->outbuffer_cursor = buffer;
    dest->written = written;

}


//摄像头采集的YUYV格式转换为JPEG格式
int compress_yuyv_to_jpeg(unsigned char *buf, unsigned char *buffer, int size, int quality)
{

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];
    unsigned char *line_buffer, *yuyv;
    int z;
    static int written;
    //int count = 0;
    //printf("%s\n", buf);

    line_buffer = calloc (WIDTH * 3, 1);
    yuyv = buf;//将YUYV格式的图片数据赋给YUYV指针
    // printf("compress start...\n");

    cinfo.err = jpeg_std_error (&jerr);
    jpeg_create_compress (&cinfo);

    /* jpeg_stdio_dest (&cinfo, file); */

    dest_buffer(&cinfo, buffer, size, &written);

    cinfo.image_width = WIDTH;
    cinfo.image_height = HEIGHT;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;


    jpeg_set_defaults (&cinfo);
    jpeg_set_quality (&cinfo, quality, TRUE);
    jpeg_start_compress (&cinfo, TRUE);

    z = 0;

    while (cinfo.next_scanline < HEIGHT)
    {
        int x;
        unsigned char *ptr = line_buffer;
        for (x = 0; x < WIDTH; x++)
        {
            int r, g, b;
            int y, u, v;
            if (!z)
                y = yuyv[0] << 8;
            else
                y = yuyv[2] << 8;

            u = yuyv[1] - 128;
            v = yuyv[3] - 128;

            r = (y + (359 * v)) >> 8;
            g = (y - (88 * u) - (183 * v)) >> 8;
            b = (y + (454 * u)) >> 8;
            //r = y + v + (v * 103) >> 8;
            //g = y - (u * 88) >> 8 - (v * 183) >> 8;
            //b = y + u + (u * 198) >> 8;

            *(ptr++) = (r > 255) ? 255 : ((r < 0) ? 0 : r);
            *(ptr++) = (g > 255) ? 255 : ((g < 0) ? 0 : g);
            *(ptr++) = (b > 255) ? 255 : ((b < 0) ? 0 : b);

            if (z++)
            {
                z = 0;
                yuyv += 4;
            }

        }
        row_pointer[0] = line_buffer;
        jpeg_write_scanlines (&cinfo, row_pointer, 1);

    }

    jpeg_finish_compress (&cinfo);
    jpeg_destroy_compress (&cinfo);
    free (line_buffer);

    return (written);

}


//读取一帧的内容
static int read_frame (void)
{

    struct v4l2_buffer buf;
    int ret;
    unsigned int i;
    CLEAR (buf);

    buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory = V4L2_MEMORY_MMAP;

    int ff = ioctl (fd, VIDIOC_DQBUF, &buf); //出列采集的帧缓冲
    if(ff<0)
        printf("failture\n");

    unsigned char src[buf.length+1];
    unsigned char dest[buf.length+1];

    assert (buf.index < n_buffers);
    // printf ("buf.index dq is %d,\n",buf.index);

    memcpy(src, buffers[buf.index].start, buf.length);
    ret = compress_yuyv_to_jpeg(src, dest,(WIDTH * HEIGHT), 80);//数据转换



    //使用udp把采集到的数据发送到手机
    sendto(iphonex,dest,ret,0,(struct sockaddr *)&phoneaddr,sizeof(phoneaddr));
	
	
    if(cap_flag==1)
    {
        FILE *photo;
        photo=fopen("./newphoto.jpg","w+");
        fwrite(dest,ret,1,photo);
        fclose(photo);
        cap_flag=0;

    }

    else
    {
        //fwrite(dest, ret, 1, file_fd);//转换后的数据写入
        lcd_draw_jpg(0,0,NULL,dest,ret,0); //显示图片 ,dest==jpeg图片数据，ret==图片字节数

    }


    ff=ioctl (fd, VIDIOC_QBUF, &buf); //重新入列
    if(ff<0)
        printf("failture VIDIOC_QBUF\n");

    return 1;

}


int get_picture()
{
    struct v4l2_capability cap;
    struct v4l2_format fmt;
    unsigned int i;
    enum v4l2_buf_type type;


    file_fd = fopen("test-mmap.jpg", "w");
    fd = open (dev_name, O_RDWR | O_NONBLOCK, 0);
    int ff=ioctl(fd, VIDIOC_QUERYCAP, &cap);//获取摄像头参数

    if(ff<0)
        printf("failture VIDIOC_QUERYCAP\n");

    struct v4l2_fmtdesc fmt1;
    int ret;

    memset(&fmt1, 0, sizeof(fmt1));
    fmt1.index = 0;

    fmt1.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    while ((ret = ioctl(fd, VIDIOC_ENUM_FMT, &fmt1)) == 0) //查看摄像头所支持的格式
    {
        fmt1.index++;
        printf("{ pixelformat = '%c%c%c%c', description = '%s' }\n",
               fmt1.pixelformat & 0xFF, (fmt1.pixelformat >> 8) & 0xFF,
               (fmt1.pixelformat >> 16) & 0xFF, (fmt1.pixelformat >> 24) & 0xFF,fmt1.description);
    }

    CLEAR (fmt);
    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    fmt.fmt.pix.width       = 640;//320;
    fmt.fmt.pix.height      = 480;//240;
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;

    fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;

    ff = ioctl (fd, VIDIOC_S_FMT, &fmt); //设置图像格式
    if(ff<0)
        printf("failture VIDIOC_S_FMT\n");


    file_length = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height; //计算图片大小
    struct v4l2_requestbuffers req;
    CLEAR (req);
    req.count               = 4;
    req.type                = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory              = V4L2_MEMORY_MMAP;

    ioctl (fd, VIDIOC_REQBUFS, &req);  //申请缓冲，count是申请的数量
    if(ff<0)
        printf("failture VIDIOC_REQBUFS\n");

    if (req.count < 1)
        printf("Insufficient buffer memory\n");

    buffers = calloc (req.count, sizeof (*buffers));//内存中建立对应空间


    for (n_buffers = 0; n_buffers < req.count; ++n_buffers)
    {
        struct v4l2_buffer buf;
        CLEAR (buf);
        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = n_buffers;
        if (-1 == ioctl (fd, VIDIOC_QUERYBUF, &buf)) //映射用户空间
            printf ("VIDIOC_QUERYBUF error\n");

        buffers[n_buffers].length = buf.length;
        buffers[n_buffers].start=mmap(NULL,buf.length,PROT_READ|PROT_WRITE,MAP_SHARED,fd,buf.m.offset); //通过mmap建立映射关系

        if (MAP_FAILED == buffers[n_buffers].start)
            printf ("mmap failed\n");
    }


    for (i = 0; i < n_buffers; ++i)
    {
        struct v4l2_buffer buf;
        CLEAR (buf);
        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = i;

        if (-1 == ioctl (fd, VIDIOC_QBUF, &buf))//申请到的缓冲进入列队
            printf ("VIDIOC_QBUF failed\n");
    }

    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (-1 == ioctl (fd, VIDIOC_STREAMON, &type)) //开始捕捉图像数据
        printf ("VIDIOC_STREAMON failed\n");

    sleep(1);
    for (;conti_run;) //这一段涉及到异步IO ==>while(1) --》 循环读取画面
    {
        fd_set fds;
        struct timeval tv;
        int r;

        FD_ZERO (&fds);//将指定的文件描述符集清空
        FD_SET (fd, &fds);//在文件描述符集合中增加一个新的文件描述符
        /* Timeout. */

        tv.tv_sec = 2;
        tv.tv_usec = 0;

        r = select (fd + 1, &fds, NULL, NULL, &tv);//判断是否可读（即摄像头是否准备好），tv是定时
        if (-1 == r)
        {
            if (EINTR == errno)
                continue;
            printf ("select err\n");
        }

        if (0 == r)
        {
            fprintf (stderr, "select timeout\n");
            exit (EXIT_FAILURE);
        }

        if (read_frame ())//如果可读，执行read_frame函数，把采集到的每一帧图像显示到开发板上
        {}//break;


    }
unmap:
    for (i = 0; i < n_buffers; ++i)
        if (-1 == munmap (buffers[i].start, buffers[i].length))
            printf ("munmap error");
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (-1 == ioctl(fd, VIDIOC_STREAMOFF, &type))
        printf("VIDIOC_STREAMOFF");
    close (fd);
    fclose (file_fd);
    exit (EXIT_SUCCESS);
    return 0;
}

void *myrecvmsg(void *arg)
{
    char buf[200];
    int addrsize=sizeof(phoneaddr);
    while(1)
    {
        usleep(1000);
        bzero(buf,200);//清零
        //聊天，收发数据，接收手机发送过来的控制命令
        recvfrom(iphonex,buf,200,0,(struct sockaddr *)&phoneaddr,&addrsize);
        printf("huawei send msg is:%s ip:%s  port:%hu\n",buf,inet_ntoa(phoneaddr.sin_addr),ntohs(phoneaddr.sin_port));
        //打印收到的命令
        if(strcmp(buf,"MUSIC_PLAY")==0)//字符串的比较
        {
            printf("music !\n");
        }

    }
}
int udp_init(int port)
{

    int ret;
    //初始化该结构体
    bindaddr.sin_family=AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);//本地IP
    bindaddr.sin_port=htons(port);//端口号也需要转换

    //买手机---》创建一个udp套接字(数据报套接字)用于通信
    iphonex=socket(AF_INET,SOCK_DGRAM,0);
    if(iphonex==-1)
    {
        printf("create socket failed!\n");
        return -1;
    }
    //绑定 ---》自己ip和端口号
    ret=bind(iphonex,(struct sockaddr *)&bindaddr,sizeof(bindaddr));
    if(ret==-1)
    {
        printf("bind failed!\n");
        return -1;
    }

    return 0;
}


void signal_handler(int sig)
{	if(sig==10)
	{
		cap_flag=1;
		
	}
	if(sig==12 || sig==2)
	{
		conti_run=0;
	}
	
}

int main(int argc, char *argv[])
{

 	if(argc != 2){
	
		fprintf(stderr, "usage: %s  <rcv_port>  \n",argv[0]);
		exit(-1);
	}

    udp_init( htons( atoi(argv[1]) ) );

	while(1)
	{
		
		
		
	}

	
 


    return 0 ;
}