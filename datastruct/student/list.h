#ifndef __LIST_H
#define __LIST_H
/**
	@File name : stu_list.h
	@Author    : YDF
	@Contact   : @qq.com
	@Date      : 2019-03-23
	@Vision    : V1.0
	@brief     : 关于学生信息管理系统链表操作头文件

**/



#include "kernellist.h"
#include "unistd.h"

typedef struct _Node
{
    int   grade;
    int   class;
    int  num;
    char  name[8];
    char  sex;

    float chinese;
    float math;
    float english;
    float chem;
    float physics;
    float biology;

    struct list_head K;


} Node,*PNode;

typedef enum _subject {grade,class,num,name,sex,chinese,math,english,chem,physics,biology} subject;


PNode list_init(void)
{
    PNode head =calloc(1,sizeof(Node));
    INIT_LIST_HEAD(&head->K);
    return head;
}

void list_add(PNode head,PNode new)
{
    //LIST_ADD_HEAD(&head->K,&new->K);
    LIST_ADD_TAIL(&head->K,&new->K);
}


void stu_add(PNode head)
{
    PNode new=calloc(1,sizeof(Node));

    printf("输入年级 ");
    scanf("%d",&(new->grade));
    printf("输入班级 ");
    scanf("%d",&(new->class));
    printf("输入学号 ");
    scanf("%d",&(new->num));
    printf("输入姓名 ");
    scanf("%s",(new->name));
    printf("输入性别(F/M) ");
    scanf(" %c",&(new->sex));
    printf("输入语文成绩 ");
    scanf("%f",&(new->chinese));
    printf("输入数学成绩 ");
    scanf("%f",&(new->math));
    printf("输入英语成绩 ");
    scanf("%f",&(new->english));
    printf("输入化学成绩 ");
    scanf("%f",&(new->chem));
    printf("输入物理成绩 ");
    scanf("%f",&(new->physics));
    printf("输入生物成绩 ");
    scanf("%f",&(new->biology));

    list_add(head,new);

}

void stu_show(PNode BIGADDR)
{
    printf("年级:%d  ",BIGADDR->grade);
    printf("班级:%d  ",BIGADDR->class);
    printf("学号:%d  ",BIGADDR->num);
    printf("姓名:%s  ",BIGADDR->name);
    printf("性别:%c  ",BIGADDR->sex);
    printf("语文:%.2f  ",BIGADDR->chinese);
    printf("数学:%.2f  ",BIGADDR->math);
    printf("英语:%.2f  ",BIGADDR->english);
    printf("化学:%.2f  ",BIGADDR->chem);
    printf("物理:%.2f  ",BIGADDR->physics);
    printf("生物:%.2f\n\n",BIGADDR->biology);
}

void list_show(PNode head)
{
    printf("年级--班级--学号--姓名--性别--语文成绩-数学成绩-英语成绩-化学成绩-物理成绩-生物成绩\n");
    struct list_head *tmp;
    PNode BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Node,K);
        printf("  %d  ",BIGADDR->grade);
        printf("  %d  ",BIGADDR->class);
        printf("  %d   ",BIGADDR->num);
        printf("%s   ",BIGADDR->name);
        printf(" %c  ",BIGADDR->sex);
        printf("\t%2.2f",BIGADDR->chinese);
        printf("\t%2.2f",BIGADDR->math);
        printf("\t%2.2f  ",BIGADDR->english);
        printf("\t%2.2f",BIGADDR->chem);
        printf("\t%2.2f",BIGADDR->physics);
        printf("\t%2.2f\n",BIGADDR->biology);
    }
}



void list_seek_num(PNode head,int s)//按学号查找
{
    struct list_head *tmp;
    PNode BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {

        BIGADDR = GetBig(tmp,Node,K);
        if(BIGADDR->num==s)
        {
            stu_show(BIGADDR);
            break;
        }
    }
    if(tmp==&head->K)
    {
        puts("not found");
    }

}

void list_seek_name(PNode head,char s[8])//按姓名查找
{
    struct list_head *tmp;
    PNode BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {

        BIGADDR = GetBig(tmp,Node,K);
        if(!strcmp(BIGADDR->name,s))
        {
            stu_show(BIGADDR);
            break;
        }
    }
    if(tmp==&head->K)
    {
        puts("not found");
    }

}

void list_seek_score(PNode head,subject sub,float s)//按sub成绩查找
{
    struct list_head *tmp;
    PNode BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {

        BIGADDR = GetBig(tmp,Node,K);
        if(sub==chinese)
        {
            if(BIGADDR->chinese==s)
            {
                stu_show(BIGADDR);
                break;
            }
        }
    }
    if(tmp==&head->K)
    {
        puts("not found");
    }

}
void stu_seek(PNode head)//查找学生
{
    char buf[8];
    int id;
    char oper;
    float score;
    printf("学号(i)\t姓名(s)\t语文(a)\t退出(q)\n");
    scanf(" %c",&oper);
    if(oper=='q')
    {
        return;
    }
    else
    {
        switch(oper)
        {
            case'i':
                printf("which [num] do you want to seek ? \n");
                scanf("%d",&id);
                list_seek_num(head,id);
                break;
            case 's':
                printf("which [name] do you want to seek ? \n");
                scanf("%s",buf);
                list_seek_name(head,buf);
                break;
            case 'a':
                printf("which score do you want to seek ? \n");
                scanf("%f",&score);
                list_seek_score(head,chinese,score);
                break;

        }
    }
}




void list_del_num(PNode head,int s)//按学号删除
{
    struct list_head *tmp;
    PNode BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Node,K);
        if(BIGADDR->num==s)
        {
            printf("%d will be del\n",s);
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

void list_del_name(PNode head,char s[8])//按姓名删除
{
    struct list_head *tmp;
    PNode BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Node,K);
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


void stu_del(PNode head)//删除学生信息
{
    char buf[8];
    int id;
    char oper;
    printf("学号(i)\t姓名(s)\t退出(q)\n");
    scanf(" %c",&oper);
    if(oper=='q')
    {
        return;
    }
    else
    {
        switch(oper)
        {
            case'i':
                printf("which [num] do you want to delete ? \n");
                scanf("%d",&id);
                list_del_num(head,id);
                break;
            case 's':
                printf("which [name] do you want to delete ? \n");
                scanf("%s",buf);
                list_del_name(head,buf);
                break;
        }
    }
}

void stu_change(PNode head)//修改学生信息
{
    char s[8];
    int num;
    char oper;
    printf("which [num]/[name] want to change? \n");
    scanf("%d %s",&num,s);

    struct list_head *tmp;
    PNode BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Node,K);
        if(!strcmp(BIGADDR->name,s)||BIGADDR->num==num)
        {
            printf("学号(i) 姓名(n) 性别(s) 语文成绩(a) 数学成绩(b) 英语成绩(c) 化学成绩(d) 物理成绩(e) 生物成绩(f)\n");
            scanf(" %c",&oper);
            switch(oper)
            {
                case 'i':
                    printf("input new num\n");
                    scanf("%d",&BIGADDR->num);
                    break;

                case 'n':
                    printf("input new name\n");
                    scanf("%s",BIGADDR->name);
                    break;
                case 's':
                    printf("input new sex\n");
                    scanf(" %c",&BIGADDR->sex);
                    break;

                case 'a':
                    printf("input new score\n");
                    scanf("%f",&BIGADDR->chinese);
                    break;

                case 'b':
                    printf("input new score\n");
                    scanf("%f",&BIGADDR->math);
                    break;

                case 'c':
                    printf("input new score\n");
                    scanf("%f",&BIGADDR->english);
                    break;

                case 'd':
                    printf("input new score\n");
                    scanf("%f",&BIGADDR->chem);
                    break;
                case 'e':
                    printf("input new score\n");
                    scanf("%f",&BIGADDR->physics);
                    break;

                case 'f':
                    printf("input new score\n");
                    scanf("%f",&BIGADDR->biology);
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






void list_add_small(PNode new_head,PNode new_node,subject sub)//由小到大插入
{

    struct list_head *t;
    PNode BIGADDR;
    t=(new_head->K).next;
    BIGADDR = GetBig(t,Node,K);
    if(sub==num)
    {
        while( (t!=&new_head->K) && (BIGADDR->num < new_node->num))
        {
            t = t->next;
            BIGADDR = GetBig(t,Node,K);
        }//new_node小于BIGADDR，退出循环

    }
    if(sub==chinese)
    {
        while( (t!=&new_head->K) && (BIGADDR->chinese < new_node->chinese))
        {
            t = t->next;
            BIGADDR = GetBig(t,Node,K);
        }//new_node小于BIGADDR，退出循环
    }
    if(sub==math)
    {
        while( (t!=&new_head->K) && (BIGADDR->math < new_node->math))
        {
            t = t->next;
            BIGADDR = GetBig(t,Node,K);
        }//new_node小于BIGADDR，退出循环
    }
    if(sub==english)
    {
        while( (t!=&new_head->K) && (BIGADDR->english < new_node->english))
        {
            t = t->next;
            BIGADDR = GetBig(t,Node,K);
        }//new_node小于BIGADDR，退出循环
    }


    //new_node插到BIGADDR前面
    INSERT_FRONT(&BIGADDR->K,&new_node->K);
}

PNode list_arrage(PNode head,subject sub)//按sub排序
{

    PNode new_head =list_init();
    struct list_head *t1,*t2;
    PNode BIGADDR;
    t1=(head->K).next;
    while(t1!=&head->K)
    {
        t2 = t1;
        t1 = t1->next;//保存移动的节点
        BIGADDR = GetBig(t2,Node,K);
        list_add_small(new_head,BIGADDR,sub);
    }

    free(head);

    return new_head;
}
PNode list_sort(PNode head)
{
    char oper;
    printf("学号(n)\t语文(a)\t数学(b)\t英语(c)\n");
    scanf(" %c",&oper);
    if(oper=='n')
    {
        head=list_arrage(head,num);
    }
    else if(oper=='a')
    {
        head=list_arrage(head,chinese);
    }
    else if(oper=='b')
    {
        head=list_arrage(head,math);
    }
    else if(oper=='c')
    {
        head=list_arrage(head,english);
    }


	return head;
}


void list_free(PNode head)//释放所有节点
{
    struct list_head *p,*q;
    PNode BIGADDR;

    LIST_FOR_EACH_SAFE(p,q,&(head->K))//q保存下一个需要释放的节点
    {
        BIGADDR = GetBig(p,Node,K);

        if(p!=&(head->K))
        {
            //    printf("free:-->%s\n",BIGADDR->name);
        }
        free(BIGADDR);
    }
    BIGADDR = GetBig(p,Node,K);
    free(BIGADDR);
    free(head);
}



void save(PNode head)//存盘保存
{
    FILE *fp =fopen("./stuinfo.txt","w+");

    if(fp == NULL)
    {
        fprintf(stderr,"fopen ./stuinfo.txt err\n");
        exit(-1);
    }
    int n=0;
    struct list_head *tmp;
    PNode BIGADDR;

    LIST_FOR_EACH(tmp,&head->K)
    {
        n++;
    }
    fprintf(fp,"%d\n",n);//n为学生数量

    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,Node,K);
        fprintf(fp,"%d %d %d %s %c %.2f %.2f %.2f %.2f %.2f %.2f\n",\
                BIGADDR->grade,BIGADDR->class,BIGADDR->num,BIGADDR->name,BIGADDR->sex,BIGADDR->chinese,BIGADDR->math,BIGADDR->english,BIGADDR->chem,BIGADDR->physics,BIGADDR->biology);
    }

    fclose(fp);
}

PNode load()//从盘加载
{
    PNode head=list_init();

    struct list_head *tmp;
    int i,n;
    if(access("./stuinfo.txt",F_OK)==0)
    {
        FILE *fp =fopen("./stuinfo.txt","r");
        if(fp == NULL)
        {
            fprintf(stderr,"fopen ./stuinfo.txt err\n");
            exit(-1);
        }

        fscanf(fp,"%d\n",&n);

        for(i=0; i<n; i++)
        {
            PNode new=calloc(1,sizeof(Node));
            fscanf(fp,"%d %d %d %s %c %f %f %f %f %f %f\n",\
                   &new->grade,&new->class,&new->num,new->name,&new->sex,\
                   &new->chinese,&new->math,&new->english,&new->chem,&new->physics,&new->biology);

            list_add(head,new);
        }

    }

    return head;
}


#endif