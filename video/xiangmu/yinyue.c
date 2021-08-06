/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdarg.h>

#define sum 3

int main(int argc,char **argv)
{

	const char *mp3list[3] = {
				"yinshipin/1.mp3",
				"yinshipin/2.mp3",
				"yinshipin/3.mp3",
			};


	char cmd[100] = {0};
	int i = 0;

	sprintf(cmd,"madplay -Q -a -10 %s &", mp3list[i]);
	system(cmd);

	char tmp[10] = {0};
	while(1){
		
		memset(cmd,0,100);
		memset(tmp,0,10);
		
		scanf("%s",tmp);

		if(!strncmp(tmp, "help",4)){
			printf("P: 暂停\nC: 继续\nO: 播放\nS: 停止\nprev: \
				上一曲\nnext: 下一曲\nQ: 退出\n");

		}else if(!strncmp(tmp, "P", 1)){
		
			system("killall -19 madplay");
		
		}else if(!strncmp(tmp, "C", 1)){
		
			system("killall -18 madplay");
		
		}else if(!strncmp(tmp, "O", 1)){
		
			sprintf(cmd, "madplay -Q -a -10 %s &", mp3list[i]);
			system(cmd);

		}else if(!strncmp(tmp, "S", 1)){
		
			system("killall -9 madplay");
		
		}else if(!strncmp(tmp, "prev", 4)){
		

			system("killall -9 madplay");

			if(--i < 0)i = sum-1;
			sprintf(cmd, "madplay -Q -a -10 %s &", mp3list[i]);
			system(cmd);

		
		}else if(!strncmp(tmp, "next", 4)){
		

			system("killall -9 madplay");

			if(++i >= sum)i = 0;
			sprintf(cmd, "madplay -Q -a -10 %s &", mp3list[i]);
			system(cmd);

		}else if(!strncmp(tmp, "Q", 1)){
		
			system("killall -9 madplay");
			break;
		}
	}



	return 0;
}//end of te main


