/**
	图书馆的图书 为一条链表 （书名 出版商  出版日期  作者  编号   借书日期 归还日期）

	学生 为一条链表 （姓名 性别 学号  借书日期 归还日期）

	老师为 一条链表 （姓名 性别 教职工编号  借书日期 归还日期）

**/
#include "book.h"
#include "stu.h"
#include "tea.h"
#include <time.h>
int main ()
{
    printf("--------图书管理系统--------\n");
    srandom(time(NULL));

    PStu studentlist=stu_init();
    PTea teacherlist=tea_init();
    PBOOK booklist=book_init();
    char buf[100]= {0};
    char oper;
    
    while(1)
    {
        printf("图书(b)\t学生(s)\t教师(t)\t退出(q)\n");
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
                    book_info(booklist);
                    
                    break;

                case's':
                    stu_info(studentlist);
                    
                    break;

                case 't':
                    tea_info(teacherlist);
                    break;

                default:
                    printf("输入正确操作符\n");
                    break;
            }
        }
        system("clear");
    }

    book_free(booklist);
    stu_free(studentlist);
    tea_free(teacherlist);
    
    return 0;
}
