#include"food.h"

PNode food_init(void)
{
    PNode foodh = list_init();

    srand(time(NULL));

    int X0 = 0;
    int Y0 = 0;
    for(int i=0; i<5; i++)
    {
        X0 = rand()%30*20;
        Y0 = rand()%24*20;

        PNode new = (PNode)calloc(1, sizeof(Node));

        new->x = X0;
        new->y = Y0;

        list_add_head(foodh, new);
    }

    return foodh;
}


void food_show(PNode foodh)
{
    PNode tmp;
    for(tmp = foodh->next; tmp!= foodh; tmp = tmp->next)
    {
        bmp_show(SNAKE_FOOD_PIC, tmp->x, tmp->y);
    }
}


void food_add(PNode foodh)
{
    srand(time(NULL));

    int X0 = rand()%30*20;
    int Y0 = rand()%24*20;

    PNode new = (PNode)calloc(1, sizeof(Node));

    new->x = X0;
    new->y = Y0;

    list_add_tail(foodh, new);


}


int food_del(PNode head,PNode foodh)
{
    int x=head->next->x;
    int y=head->next->y;
	
    PNode tmp;
    for(tmp=foodh->next; tmp!=foodh; tmp=tmp->next)
    {
        if( x==tmp->x && y==tmp->y)
        {
            list_del(foodh,x,y);
			printf("food x=%d,y=%d",x,y);
			return 1;
        }
		
    }
	return 0;
}




