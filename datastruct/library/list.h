#ifndef __LIST_H
#define __LIST_H

#include "kernellist.h"


typedef struct _Book
{

    char title[8];
    char publisher[8];
    char publish_date[8];
    char author[8];
    char id[8];
    char lend_date[8];
    char return_date[8];


    struct list_head K;

} Book,*PBook;

typedef struct _Stu
{
    char name[8];
    char num[8];
    char sex;
    char lend_date[8];
    char return_date[8];


    struct list_head K;

} Stu,*PStu;


typedef struct _Tea
{

    char name[8];
    char num[8];
    char sex;
    char lend_date[8];
    char return_date[8];


    struct list_head K;

} Tea,*PTea;




/*图书*/
PBook book_init(void)//图书链表初始化
{
    PBook head =calloc(1,sizeof(Book));
    INIT_LIST_HEAD(&head->K);
    return head;
}
void book_list_add(PBook head,PBook new)//图书链表添加
{
    //LIST_ADD_HEAD(&head->K,&new->K);
    LIST_ADD_TAIL(&head->K,&new->K);
}

void book_add(PBook head)//图书信息添加
{
    PBook new=calloc(1,sizeof(Book));

    printf("输入书名 ");
    scanf("%s",(new->title));
    printf("输入出版商 ");
    scanf("%s",(new->publisher));
    printf("输入出版日期 ");
    scanf("%s",(new->publish_date));
    printf("输入作者 ");
    scanf("%s",(new->author));
    printf("输入编号 ");
    scanf("%s",(new->id));
    printf("输入借书日期 ");
    scanf("%s",(new->lend_date));
    printf("输入归还日期 ");
    scanf("%s",(new->return_date));

    book_list_add(head,new);

}

void book_show(PBook head)//显示所有图书
{
    printf("书名 ");

    printf("出版商 ");

    printf("出版日期 ");

    printf("作者 ");

    printf("编号 ");

    printf("借书日期 ");

    printf("归还日期 ");

    puts("");

    struct list_head *tmp;
    PBook BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Book,K);
        printf("%8s",BIGADDR->title);
        printf("%8s",BIGADDR->publisher);
        printf("%8s",BIGADDR->publish_date);
        printf("%8s",BIGADDR->author);
        printf("%8s",BIGADDR->id);
        printf("%8s",BIGADDR->lend_date);
        printf("%8s",BIGADDR->return_date);
        puts("");
    }

}


void book_seek_title(PBook head,char s[8])//按书名查找
{
    struct list_head *tmp;
    PBook BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {

        BIGADDR = GetBig(tmp,Book,K);
        if(!strcmp(BIGADDR->title,s))
        {
            //    book_show(BIGADDR);
            printf("%8s",BIGADDR->title);
            printf("%8s",BIGADDR->publisher);
            printf("%8s",BIGADDR->publish_date);
            printf("%8s",BIGADDR->author);
            printf("%8s",BIGADDR->id);
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

void book_del_title(PBook head,char s[8])//按书名删除
{
    struct list_head *tmp;
    PBook BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Book,K);
        if(!strcmp(BIGADDR->title,s))
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




void book_seek(PBook head)//图书按书名检索
{
    char buf[8];
    printf("which book do you want to seek ? \n");
    scanf("%s",buf);
    book_seek_title(head,buf);

}

void book_del(PBook head)//图书按书名删除
{
    char buf[8];
    printf("which book do you want to delete? \n");
    scanf("%s",buf);
    book_del_title(head,buf);
}

void book_change(PBook head)//图书按书名修改
{
    char s[8];
    char oper;
    printf("which book want to change? \n");
    scanf("%s",s);

    struct list_head *tmp;
    PBook BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Book,K);
        if(!strcmp(BIGADDR->title,s))
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
            book_show(BIGADDR);
            break;
        }
    }

    if(tmp==&head->K)
    {
        puts("not found");
    }

}

void book_free(PBook head)//释放图书所有节点
{
    struct list_head *p,*q;
    PBook BIGADDR;

    LIST_FOR_EACH_SAFE(p,q,&(head->K))//q保存下一个需要释放的节点
    {
        BIGADDR = GetBig(p,Book,K);

        if(p!=&(head->K))
        {
            //    printf("free:-->%s\n",BIGADDR->name);
        }
        free(BIGADDR);
    }
    BIGADDR = GetBig(p,Book,K);
    free(BIGADDR);
    free(head);
}

void book_info(PBook head)//图书信息
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
                        book_add(head);
                    break;

                case'c':
                        book_show(head);

                    break;

                case 'd':
                    book_del(head);
                    break;



                default:
                    printf("输入正确操作符\n");
                    break;
            }
        }
    }


}



/*学生*/
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

void stu_show(PBook head)//显示所有图书
{
    printf("书名 ");

    printf("出版商 ");

    printf("出版日期 ");

    printf("作者 ");

    printf("编号 ");

    printf("借书日期 ");

    printf("归还日期 ");

    puts("");

    struct list_head *tmp;
    PBook BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Book,K);
        printf("%8s",BIGADDR->title);
        printf("%8s",BIGADDR->publisher);
        printf("%8s",BIGADDR->publish_date);
        printf("%8s",BIGADDR->author);
        printf("%8s",BIGADDR->id);
        printf("%8s",BIGADDR->lend_date);
        printf("%8s",BIGADDR->return_date);
        puts("");
    }

}


void book_seek_title(PBook head,char s[8])//按书名查找
{
    struct list_head *tmp;
    PBook BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {

        BIGADDR = GetBig(tmp,Book,K);
        if(!strcmp(BIGADDR->title,s))
        {
            //    book_show(BIGADDR);
            printf("%8s",BIGADDR->title);
            printf("%8s",BIGADDR->publisher);
            printf("%8s",BIGADDR->publish_date);
            printf("%8s",BIGADDR->author);
            printf("%8s",BIGADDR->id);
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

void book_del_title(PBook head,char s[8])//按书名删除
{
    struct list_head *tmp;
    PBook BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Book,K);
        if(!strcmp(BIGADDR->title,s))
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




void book_seek(PBook head)//图书按书名检索
{
    char buf[8];
    printf("which book do you want to seek ? \n");
    scanf("%s",buf);
    book_seek_title(head,buf);

}

void book_del(PBook head)//图书按书名删除
{
    char buf[8];
    printf("which book do you want to delete? \n");
    scanf("%s",buf);
    book_del_title(head,buf);
}

void book_change(PBook head)//图书按书名修改
{
    char s[8];
    char oper;
    printf("which book want to change? \n");
    scanf("%s",s);

    struct list_head *tmp;
    PBook BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Book,K);
        if(!strcmp(BIGADDR->title,s))
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
            book_show(BIGADDR);
            break;
        }
    }

    if(tmp==&head->K)
    {
        puts("not found");
    }

}

void book_free(PBook head)//释放图书所有节点
{
    struct list_head *p,*q;
    PBook BIGADDR;

    LIST_FOR_EACH_SAFE(p,q,&(head->K))//q保存下一个需要释放的节点
    {
        BIGADDR = GetBig(p,Book,K);

        if(p!=&(head->K))
        {
            //    printf("free:-->%s\n",BIGADDR->name);
        }
        free(BIGADDR);
    }
    BIGADDR = GetBig(p,Book,K);
    free(BIGADDR);
    free(head);
}

void book_info(PBook head)//图书信息
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
                        book_add(head);
                    break;

                case'c':
                        book_show(head);

                    break;

                case 'd':
                    book_del(head);
                    break;



                default:
                    printf("输入正确操作符\n");
                    break;
            }
        }
    }


}



/*教师*/
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