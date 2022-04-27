#ifndef __TEA_H
#define __TEA_H

#include "kernellist.h"

/*教师*/

typedef struct _Tea
{

    char name[12];
    char num[12];
    char sex;
    char lend_date[12];
    char return_date[12];


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

    printf("输入姓名:");
    scanf("%s",(new->name));
    printf("输入性别:");
    scanf(" %c",&(new->sex));
    printf("输入工号:");
    scanf("%s",(new->num));
    printf("输入借书日期:");
    scanf("%s",(new->lend_date));
    printf("输入归还日期:");
    scanf("%s",(new->return_date));

    tea_list_add(head,new);

}
void tea_free(PTea head)//释放图书所有节点
{
    struct list_head *p,*q;
    PTea BIGADDR;

    LIST_FOR_EACH_SAFE(p,q,&(head->K))//q保存下一个需要释放的节点
    {
        BIGADDR = GetBig(p,Tea,K);

        if(p!=&(head->K))
        {
            //    printf("free:-->%s\n",BIGADDR->name);
        }
        free(BIGADDR);
    }
    BIGADDR = GetBig(p,Tea,K);
    free(BIGADDR);
    free(head);
}
void tea_info(PTea head)//学生信息
{

    char buf[10]= {0};
    char oper;

    while(1)
    {
        printf("添加(a)\t查询(c)\t删除(d)\t退出(q)\n");
        scanf(" %c",&oper);
        if(oper=='q')
        {
            return;
        }
        else
        {
            switch(oper)
            {
                case'a':
                        tea_add(head);
                    break;

                case'c':
                        //tea_show(head);

                    break;

                case 'd':
                    //tea_del(head);
                    break;



                default:
                    printf("输入正确操作符\n");
                    break;
            }
        }
    }


}









#endif
