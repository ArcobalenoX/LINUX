/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <linux/mman.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>

/**********IO header*************/
#define  _PG_IO
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>


#include "touch.h"
#include "jpeg_show.h"

#include "Package.h"
#define FIFO_FILE	"/tmp/myfifo"

#define sum 3


int main(int argc,char **argv)
{


    int x,y;
    const char *mp3list[3] =
    {
        "yinshipin/1.mp3",
        "yinshipin/2.mp3",
        "yinshipin/3.mp3",
    };


    while(1)
    {
        jpeg_show("./main.jpg");
        get_xy(&x, &y);
        printf("x:%d  y:%d\n",x,y);


        if(100<x && x<250 && 300<y && y<400)
        {
            jpeg_show("./yinyue.jpg");
            printf("进入音乐界面\n");
            char cmd[100] = {0};
            int i = 0;
            int flag=0;//0为停止状态 1为播放状态

            while(1)
            {
                get_xy(&x, &y);
                printf("x:%d  y:%d\n",x,y);
                memset(cmd,0,100);


                if(flag == 0 && (250<x&&x<400) && 400<y)
                {

                    sprintf(cmd, "madplay -Q -a -10 %s &", mp3list[i]);
                    system(cmd);
                    printf("已播放\n");
                    flag=1;

                }

                else if( flag == 1 && (250<x&&x<400) && 400<y  )
                {
                    system("killall -19 madplay");
                    printf("已暂停\n");
                    flag=2;

                }

                else if(flag == 2 && (250<x&&x<400) && 400<y)
                {

                    system("killall -18 madplay");
                    printf("已继续\n");
                    flag=1;

                }


                else if(50<x&&x<200&&400<y)
                {


                    system("killall -9 madplay");

                    if(--i < 0)i = sum-1;
                    sprintf(cmd, "madplay -Q -a -10 %s &", mp3list[i]);
                    system(cmd);
                    printf("前一首\n");


                }
                else if(450<x&&x<580&&400<y)
                {


                    system("killall -9 madplay");

                    if(++i >= sum)i = 0;
                    sprintf(cmd, "madplay -Q -a -10 %s &", mp3list[i]);
                    system(cmd);

                    printf("后一首\n");

                }
                else if(x>600&&x<750&&400<y)
                {

                    system("killall -9 madplay");
                    printf("退出音乐播放\n");
                    break;
                }
            }
        }
        else if(350<x && x<500 && 300<y && y<400)
        {
            jpeg_show("./shipin.jpg");
            printf("进入视频界面\n");
            while(1)
            {
                get_xy(&x, &y);
                printf("x:%d  y:%d\n",x,y);

                //1. 创建管道文件 + 打开
                if(access(FIFO_FILE, F_OK)) //不存在
                {
                    mkfifo(FIFO_FILE, O_CREAT|0666);
                }

                int fd = open(FIFO_FILE, O_RDWR);

                if(y<300)
                {
                    //2. 播放视频
                    system("mplayer -quiet -zoom -x 800 -y 400 -slave -input file=/tmp/myfifo -loop 0 -playlist ./avi.list &");
                }

                //3. 管道控制
                if((275<x&&x<375) && 400<y)
                {

                    write(fd, "pause\n",6);
                    printf("暂停\n");
                }
                else if((00<x&&x<100) && 400<y)
                {
                    write(fd, "key_down_event 60\n",18);
                    printf("前一个\n");

                }

                else if((500<x&&x<600) && 400<y)
                {

                    write(fd, "key_down_event 62\n",18);
                    printf("后一个\n");
                }

                else if((150<x&&x<250) && 400<y)
                {

                    write(fd, "seek -10\n",9);
                    printf("快退n");
                }
                else if((400<x&&x<480) && 400<y)
                {
                    write(fd, "seek 10\n",8);
                    printf("快进\n");
                }
                else if((600<x&&x<800) && 400<y)
                {

                    write(fd, "quit\n",5);
                    printf("退出视频播放\n");
                    break;

                }


            }
        }
        else if(550<x && x<750 && 300<y && y<400)
        {
            printf("退出程序\n");
            break;
        }

    }
    return 0;
}//end of te main


