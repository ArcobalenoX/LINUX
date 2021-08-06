#ifndef __STU_H
#define __STU_H

#include "kernellist.h"

/*学生*/

typedef struct _Stu
{
    char name[8];
    char num[8];
    char sex;
    char lend_date[8];
    char return_date[8];


    struct list_head K;

} Stu,*PStu;



PStu stu_init(void)//学生链表初始化
{
    PStu head =calloc(1,sizeof(Stu));
    INIT_LIST_HEAD(&head->K);
    return head;
}
void stu_list_add(PStu head,PStu new)//学生链表添加
{
    //LIST_ADD_HEAD(&head->K,&new->K);
    LIST_ADD_TAIL(&head->K,&new->K);
}



void stu_add(PStu head)//学生信息添加
{
    PStu new =calloc(1,sizeof(Stu));

    printf("输入姓名 ");
    scanf("%s",(new->name));
    printf("输入性别 ");
    scanf(" %c",&(new->sex));
    printf("输入学号 ");
    scanf("%s",(new->num));
    printf("输入借书日期 ");
    scanf("%s",(new->lend_date));
    printf("输入归还日期 ");
    scanf("%s",(new->return_date));

    stu_list_add(head,new);

}

void stu_show(PStu head)//显示所有学生
{
    printf("姓名   ");

    printf("性别   ");

    printf("学号   ");

    printf("借书日期   ");

    printf("归还日期   ");

    puts("");

    struct list_head *tmp;
    PStu BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Stu,K);
        printf("%-8s",BIGADDR->name);
        printf("%-4c",BIGADDR->sex);
        printf("%-12s",BIGADDR->num);
        printf("%-12s",BIGADDR->lend_date);
        printf("%-12s",BIGADDR->return_date);
        puts("");
    }

}


void stu_seek_name(PStu head,char s[8])//按姓名查找
{
    struct list_head *tmp;
    PStu BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {

        BIGADDR = GetBig(tmp,Stu,K);
        if(!strcmp(BIGADDR->name,s))
        {
            //    Stu_show(BIGADDR);
            printf("%8s",BIGADDR->name);
            printf("%c",BIGADDR->sex);
            printf("%8s",BIGADDR->num);
            printf("%8s",BIGADDR->lend_date);
            printf("%8s",BIGADDR->return_date);
            break;
        }
    }
    if(tmp==&head->K)
    {
        puts("not found");
    }

}

void stu_del_name(PStu head,char s[8])//按姓名删除
{
    struct list_head *tmp;
    PStu BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Stu,K);
        if(!strcmp(BIGADDR->name,s))
        {
            printf("%s will be del\n",s);
            LIST_DEL(&BIGADDR->K);
            free(BIGADDR);
            break;
        }
        if(tmp==&head->K)
        {
            puts("not found");
        }

    }
}




void stu_seek(PStu head)//学生按姓名检索
{
    char buf[8];
    printf("which Student do you want to seek ? \n");
    scanf("%s",buf);
    stu_seek_name(head,buf);

}

void stu_del(PStu head)//学生按姓名删除
{
    char buf[8];
    printf("which Student do you want to delete? \n");
    scanf("%s",buf);
    stu_del_name(head,buf);
}

void stu_change(PStu head)//学生按姓名修改
{
    char s[8];
    char oper;
    printf("which Student want to change? \n");
    scanf("%s",s);

    struct list_head *tmp;
    PStu BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Stu,K);
        if(!strcmp(BIGADDR->name,s))
        {
            printf("借书日期(l)\t归还日期(r)\n");
            scanf(" %c",&oper);
            switch(oper)
            {

                case 'l':

                    break;

                default:
                    printf("输入正确操作符\n");
                    break;
            }
            stu_show(BIGADDR);
            break;
        }
    }

    if(tmp==&head->K)
    {
        puts("not found");
    }

}

void stu_free(PStu head)//释放学生所有节点
{
    struct list_head *p,*q;
    PStu BIGADDR;

    LIST_FOR_EACH_SAFE(p,q,&(head->K))//q保存下一个需要释放的节点
    {
        BIGADDR = GetBig(p,Stu,K);

        if(p!=&(head->K))
        {
            //    printf("free:-->%s\n",BIGADDR->name);
        }
        free(BIGADDR);
    }
    BIGADDR = GetBig(p,Stu,K);
    free(BIGADDR);
    free(head);
}

void stu_info(PStu head)//学生信息
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
                        stu_add(head);
                    break;

                case'c':
                        stu_show(head);

                    break;

                case 'd':
                    stu_del(head);
                    break;



                default:
                    printf("输入正确操作符\n");
                    break;
            }
        }
    }


}











#endif