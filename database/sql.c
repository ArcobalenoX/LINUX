/********std header**********/
#define  _PG_std
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <errno.h>
#include <sqlite3.h>

#define SQL_DB "./test.db"


int flag=1;
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;

    if(flag==1)
    {
		printf("\n");
        for(i=0; i<argc; i++)
        {
            printf("%s\t", azColName[i]);

        }
        flag++;
        printf("\n-------------------------------\n");
    }
    for(i=0; i<argc; i++)
    {
        printf("%s\t", argv[i] ? argv[i] : "NULL");
    }

    /*
    for(i=0; i<argc; i++)
    {
        printf("%s = %s\t", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    */
    printf("\n");
    return 0;
}

void msg_err_handler(int ret,char *msg_err,char *msg_ok)
{
    if( ret != SQLITE_OK )
    {
        fprintf(stderr, "SQL error: %s\n", msg_err);
        sqlite3_free(msg_err);
    }
    else
    {
        fprintf(stdout, "SQL : %s\n",msg_ok);
    }
}

void sql_insert(sqlite3*sqldb)
{
    int id;
    char name[50];
    float score;
    char addr[50];
    char *msg_err;
    int rc;

    printf("input id:");
    scanf("%d",&id);
    printf("input name:");
    scanf("%s",name);
    printf("input score:");
    scanf("%f",&score);
    printf("input addr:");
    scanf("%s",addr);

    char cmd[256];
    sprintf(cmd,"insert into stu (id,name,score,addr) values(%d,'%s',%.2f,'%s');",id,name,score,addr);
    printf("%s\n",cmd);
    rc=sqlite3_exec(sqldb,cmd,NULL,NULL,&msg_err);
    msg_err_handler(rc,msg_err,"insert ok");

}

void sql_delete(sqlite3*sqldb)
{
    int id;
    char *msg_err;
    int rc;
    char cmd[256];
    printf("input id:");
    scanf("%d",&id);
    sprintf(cmd,"delete from stu where id=%d",id);
    rc=sqlite3_exec(sqldb,cmd,callback,0,&msg_err);
    msg_err_handler(rc,msg_err,"delete ok");

}

void sql_select(sqlite3*sqldb)
{
    char *msg_err;
    int rc;
    char cmd[256]="select * from stu;";
  
    rc=sqlite3_exec(sqldb,cmd,callback,0,&msg_err);
    msg_err_handler(rc,msg_err,"select ok");
    flag=1;
}

void sql_update(sqlite3*sqldb)
{
    int id;
    char *msg_err;
    int rc;
    char cmd[256];
    char col[50]= {0};
    char new[50]= {0};
    printf("input id:");
    scanf("%d",&id);
    printf("column=new_date\n");
    scanf("%s=%s",col,new);
    sprintf(cmd,"update stu set %s %s where id=%d;",col,new,id);
    printf("%s\n",cmd);
    rc=sqlite3_exec(sqldb,cmd,callback,0,&msg_err);
    msg_err_handler(rc,msg_err,"update ok");

}

void sql_sort(sqlite3*sqldb)
{
    char *msg_err;
    int rc;
    char cmd[256];
    char buf[50];
    printf("order by  ");
    scanf("%s",buf);
    sprintf(cmd,"select * from stu order by %s;",buf);
    rc=sqlite3_exec(sqldb,cmd,callback,0,&msg_err);
    msg_err_handler(rc,msg_err,"sort ok");
    flag=1;
}

void sql_create(sqlite3*sqldb)
{
	char *cmd;
    cmd="create table stu("\
        "id int primary key not null,"\
        "name text unique not null,"\
        "score float check(0<=score<=100),"\
        "addr text);";
    sqlite3_exec(sqldb,cmd,NULL,NULL,NULL);
	
}

int main(int argc,char **argv)
{
    sqlite3* sqldb;
    sqlite3_open(SQL_DB,&sqldb);
	sql_create(sqldb);
	
	system("clear");
    printf("\t\t\t学生信息管理系统\n");
    printf("\t\t\t1. 插入学生信息\n");
    printf("\t\t\t2. 查看学生信息\n");
    printf("\t\t\t3. 删除学生信息\n");
    printf("\t\t\t4. 修改学生信息\n");
    printf("\t\t\t5. 排序学生信息\n");
    printf("\t\t\t6. 退出管理系统\n");


    char ch;
    while(1)
    {
        scanf("%c",&ch);
        if(ch=='6')
            break;
        switch(ch)
        {
            case'1':
                    sql_insert(sqldb);
                break;
            case'2':
                    sql_select(sqldb);
                break;
            case'3':
                    sql_delete(sqldb);
                break;
            case'4':
                    sql_update(sqldb);
                break;
			case'5':
				sql_sort(sqldb);
				break;
            default:break;       
        };

    }

    sqlite3_close(sqldb);
    return 0;
}//end of te main


