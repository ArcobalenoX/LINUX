
//#include "list.h"
/**
	图书馆的图书 为一条链表 （书名 出版商  出版日期  作者  编号   借书日期 归还日期）

	学生 为一条链表 （姓名 性别 学号  借书日期 归还日期）

	老师为 一条链表 （姓名 性别 教职工编号  借书日期 归还日期）

**/
#include "book.h"
#include "stu.h"
#include "tea.h"
int main ()
{
    printf("--------图书管理系统--------\n");
    PBook BOOK=book_init();
    PStu STU=stu_init();
    PTea TEA=tea_init();

    char buf[20]= {0};
    char oper;
    while(1)
    {
        printf("书目(b)\t学生(s)\t教师(t)\t退出(q)\n");
        scanf(" %c",&oper);
        if(oper=='q')
        {
            break;
        }
        else
        {
            switch(oper)
            {
                case'b':
                        book_info(BOOK);
                    break;

                case's':
                    stu_info(STU);

                    break;

                case 't':
                //    teach_info(TEA);
                    break;



                default:
                    printf("输入正确操作符\n");
                    break;
            }
        }

    }

    book_free(BOOK);
    return 0;
}