#include "touch.h"

void get_xy(int *x, int *y){
	
	int fd_touch   = open("/dev/input/event0", O_RDONLY);
	if(fd_touch ==  -1){
	
		perror("open touch screen err");
		exit(-1);
	}

	struct input_event ts;

	while(1){
	
		read(fd_touch, &ts, sizeof(ts));

		if(ts.type == EV_ABS){//绝对位移事件  触摸屏事件
			if(ts.code == ABS_X){
				*x =ts.value;
			}else if(ts.code == ABS_Y){
			
				*y = ts.value;
			}
		}	

		if(ts.code == BTN_TOUCH && ts.value == 0){
			break;
		}
	
	
	}
	
	
	
	

	close(fd_touch);

	return;
}



