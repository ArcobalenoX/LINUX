#ifndef __TEA_H
#define __TEA_H

#include "kernellist.h"

/*教师*/

typedef struct _Tea
{

    char name[8];
    char num[8];
    char sex;
    char lend_date[8];
    char return_date[8];


    struct list_head K;

} Tea,*PTea;



PTea tea_init(void)//教师链表初始化
{
    PTea head =calloc(1,sizeof(Tea));
    INIT_LIST_HEAD(&head->K);
    return head;
}

void tea_list_add(PTea head,PTea new)//教师链表添加
{
    //LIST_ADD_HEAD(&head->K,&new->K);
    LIST_ADD_TAIL(&head->K,&new->K);
}

void tea_add(PTea head)//教师信息添加
{
    PTea new =calloc(1,sizeof(Tea));

    printf("输入姓名 ");
    scanf("%s",(new->name));
    printf("输入性别 ");
    scanf(" %c",&(new->sex));
    printf("输入工号 ");
    scanf("%s",(new->num));
    printf("输入借书日期 ");
    scanf("%s",(new->lend_date));
    printf("输入归还日期 ");
    scanf("%s",(new->return_date));

    tea_list_add(head,new);

}










#endif