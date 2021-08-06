#ifndef __SNAKE_H
#define __SNAKE_H

#include "bmp_show.h"
#include "touch.h"
#include "list.h"
#include <time.h>

#define SNAKE_HEAD_PIC 		"./SNK_pic/h.bmp"
#define SNAKE_BODY_PIC 		"./SNK_pic/s.bmp"
#define SNAKE_BCK_PIC		"./SNK_pic/snake.bmp"
#define GAME_OVER			"./SNK_pic/over.bmp"
#define PLAY				"./SNK_pic/play.bmp"
#define	QUIT 				"./SNK_pic/quit.bmp"

PNode snake_init(void);
void snake_show(PNode head);
void snk_mv(PNode head,int x,int y);
void snake_add(PNode head);

#endif //end of __SNAKE_H

