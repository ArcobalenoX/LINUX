#include "list.h"


int main ()
{
    PNode head=list_init();

    int i;char buf[8];
    for(i=0; i<3; i++)
    {
        PNode new=calloc(1,sizeof(Node));
		
        printf("输入序列号  ");
        scanf("%d",&(new->data));
        printf("输入车牌号(8位)  ");
        scanf("%s",(new->num));
        printf("输入颜色(0:黑色 1:白色 2:绿色 3:红色 4:蓝色 5:黄色)  ");
        scanf(" %c",&(new->color));
		
        list_add(head,new);

    }
    list_show(head);
	puts("");

    printf("which 序列号 to seek and del\n");
    scanf("%d",&i);
    list_seek_data(head,i);
    list_del_data(head,i);
    list_show(head);
	puts("");
	
	printf("which 车牌号 to seek and del\n");
    scanf("%s",buf);
	list_seek_num(head,buf);
    list_del_num(head,buf);
    list_show(head);
	puts("");
	
	printf("will free all\n");
    list_free(head);

    return 0;
}