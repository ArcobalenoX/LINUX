#include "bmp_show.h"
#include "touch.h"
#include "list.h"
#include "snake.h"
#include "food.h"
#include <pthread.h>

PNode head;
PNode foodh;
void *routine1(void *argc)
{
    sleep(1);
    int x,y;
    while(1)
    {
        get_xy(&x, &y);
        snk_mv(head,x,y);


    }
    pthread_exit(NULL);
}

void *routine2(void *argc)
{
    sleep(1);
    int count;
    while(1)
    {

        PNode tmp;
        count = 0;
        for(tmp=foodh->next; tmp!=foodh; tmp=tmp->next)
        {
            count++;
        }
        if(count<5)
        {
            food_add(foodh);
        }
        if(food_del(head,foodh)==1)
        {
            snake_add(head);
        }


        food_show(foodh);
    }

    pthread_exit(NULL);
}


int main(int argc,char **argv)
{
    head = snake_init();
    foodh =food_init();

    snake_show(head);


    pthread_t tid1,tid2;
    int ret = pthread_create(&tid1,NULL,routine1,NULL);
    if(ret!=0)
    {
        perror("pthread_create");
        exit(-1);
    }
    ret = pthread_create(&tid2,NULL,routine2,NULL);
    if(ret!=0)
    {
        perror("pthread_create");
        exit(-1);
    }

    PNode p,q;

    while(1)
    {
        sleep(1);
        p=head->next;
        q=p->next;
        if( p->x > q->x || q->x<0)//自动右移
            snk_mv(head,750,385);
        else if( p->x < q->x||q->x>600)//自动左移
            snk_mv(head,650,385);
        else if( p->y > q->y||q->y<0)//自动上移
            snk_mv(head,700,420);
        else if( p->y < q->y||q->y>480)//自动下移
            snk_mv(head,700,350);


    }



    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

    list_free(foodh);
    list_free(head);
    pthread_exit(NULL);
    return 0;
}


