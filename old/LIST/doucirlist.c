#include"doucirlist.h"

int main(void)
{

	PNODE head=list_init();
	int i;
	puts("输入中...\n");
	for(i=0;i<10;i++)
	{
		list_add_head(head,i);
	}
	list_pri(head);	
	list_del(head,5);
	list_del(head,3);
	list_pri(head);
	list_free(head);
	
	
	return 0;
}