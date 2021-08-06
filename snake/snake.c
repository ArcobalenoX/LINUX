#include "snake.h"


PNode snake_init(void)
{

    PNode head = list_init();

    bmp_show(SNAKE_BCK_PIC, 0, 0);

    srand(time(NULL));

    int X0 = rand()%15*20 + 200;
    int Y0 = rand()%15*20 + 100;

    int i;

    for(i=0; i<5; i++)
    {

        PNode new = (PNode)calloc(1, sizeof(Node));

        new->x = X0 - i*20;
        new->y = Y0;

        list_add_tail(head, new);
    }

    return head;
}
void snake_add(PNode head)
{
    int offset_x=0,offset_y=0;
    PNode p,q;
    p=head->prev;
    q=p->prev;
    if(p->x<q->x)
    {
        offset_x=-20;
        offset_y=0;
    }
    else if(p->x>q->x)
    {
        offset_x=20;
        offset_y=0;

    }
    else if(p->y<q->y)
    {
        offset_x=0;
        offset_y=-20;
    }
    else if(p->y>q->y)
    {
        offset_x=0;
        offset_y=20;

    }


    PNode new = (PNode)calloc(1, sizeof(Node));
    new->x = p->x+offset_x;
    new->y = p->y+offset_y;
    list_add_tail(head,new);

}


void snake_show(PNode head)
{

    PNode tmp;
    int i=0;

    for(tmp = head->next; tmp!= head; tmp = tmp->next)
    {

        if(++i == 1)
        {
            bmp_show(SNAKE_HEAD_PIC, tmp->x, tmp->y);
        }
        else
        {

            bmp_show(SNAKE_BODY_PIC, tmp->x, tmp->y);
        }
    }
}

void snk_mv(PNode head,int x,int y)
{


    char left,right,up,down;
    PNode p,q;
    p=head->next;
    q=p->next;
    left=right=up=down=1;
    if(p->x<q->x)
    {
        right=0;
    }
    if(p->x>q->x)
    {
        left=0;

    }
    if(p->y<q->y)
    {
        down=0;

    }
    if(p->y>q->y)
    {
        up=0;
    }
    PNode new = (PNode)calloc(1, sizeof(Node));
    new->x = head->next->x;
    new->y = head->next->y;
    if(left!=0&&x>630 && x<670 && y>370 && y<410) //left
    {
        new->x = head->next->x - 20;
        //越界判断
        if(new->x < 0) new->x += 600;
    }
    else if(right!=0&&x>730 && x< 770 && y>370 && y< 410)  //right
    {

        new->x = head->next->x + 20;
        //越界判断
        if(new->x > 600) new->x -= 600;

    }

    else if(up!=0&&x>680 && x<720 && y>330 && y< 370)  //up
    {

        new->y = head->next->y-20;
        //越界判断
        if(new->y < 0) new->y += 480;

    }

    else if(down!=0&&x>680 && x<720 && y>400 && y<440)  //down
    {

        new->y = head->next->y+20;
        //越界判断
        if(new->y > 480) new->y -= 480;
    }

    //判断是否撞身
    PNode tmp;
    for(tmp=head->next->next; tmp!=head->next; tmp=tmp->next)
    {
        if(tmp->x==head->next->x && tmp->y==head->next->y)
        {
           bmp_show(GAME_OVER,300,200);
        }
    }



    bmp_show(SNAKE_BODY_PIC, head->next->x, head->next->y);//把原来到 头 变 身体

    list_add_head(head, new);//增加新的头到链表

    bmp_show(SNAKE_HEAD_PIC, new->x, new->y);//显示新的头

    bmp_show_bck(SNAKE_BCK_PIC, head->prev->x, head->prev->y);//从LCD上清除原来的尾巴

    list_del_tail(head);//删除链表中旧的尾巴

}







