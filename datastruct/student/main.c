#include "list.h"
/**
学生的  年级  班级  姓名 性别  学号  手机号
		语文成绩   数学成绩  英语成绩   化学成绩  物理成绩  生物成绩
	--》插入学生信息  修改学生信息   删除学生信息  查找学生信息
	  修改某个学生成绩  按照某一门成绩排序
**/

int main ()
{
    system("clear");
    printf("----------学生信息管理系统----------\n");
    PNode head=list_init();
    head=load();

    char oper;
    while(1)
    {
        printf("排序(w)\t查询(s)\t添加(a)\t修改(c)\t删除(d)\t退出(q)\n");
        scanf(" %c",&oper);
        if(oper=='q')
        {
            save(head);
            list_free(head);
            break;
        }
        else
        {
            switch(oper)
            {
                case'w':             
					head=list_sort(head);
                    list_show(head);
                    break;

                case 's':
                    stu_seek(head);
                    break;

                case 'a':
                    stu_add(head);
                    break;

                case 'c':
                    stu_change(head);
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


    return 0;
}