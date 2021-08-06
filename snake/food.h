#ifndef __FOOD_H
#define __FOOD_H

#include "bmp_show.h"
#include "touch.h"
#include "list.h"
#include <time.h>

#define SNAKE_FOOD_PIC 		"./SNK_pic/food.bmp"
#define SNAKE_BCK_PIC		"./SNK_pic/snake.bmp"

PNode food_init(void);
void food_show(PNode head);
void food_add(PNode head);
int food_del(PNode head,PNode foodh);


#endif //end of __SNAKE_H
