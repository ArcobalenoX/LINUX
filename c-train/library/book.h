#ifndef __BOOK_H
#define __BOOK_H

#include "kernellist.h"

/*图书*/

#define ARRAY_SIZE 64

typedef struct _BOOK
{

    char title[ARRAY_SIZE];
    char publisher[ARRAY_SIZE];
    char publish_date[ARRAY_SIZE];
    char author[ARRAY_SIZE];
    char id[ARRAY_SIZE];
    char lend_date[ARRAY_SIZE];
    char return_date[ARRAY_SIZE];


    struct list_head K;

} BOOK,*PBOOK;

char books[][64] = {"程序设计","爵迹","三重门","平凡的世界","钱钟书传","红高梁","史记","白鹿原","繁星","我们仨"};
char authors[][64] = {"谭浩强","郭敬明","韩寒","路遥","钱钟书","莫言","陈忠实","司马迁","冰心","杨绛"};


PBOOK book_init(void)//图书链表初始化
{
    PBOOK head =malloc(sizeof(BOOK));
    INIT_LIST_HEAD(&head->K);
    return head;
}
PBOOK book_list_add(PBOOK head,PBOOK newbook)//图书链表添加节点
{
    //LIST_ADD_HEAD(&head->K,&newbook->K);
    LIST_ADD_TAIL(&head->K,&newbook->K);
    return head;
}


void book_show(PBOOK BIGADDR)//显示一本图书
{
 printf("%s|%s|%s|%s|%s|%s|%s\n",\
            BIGADDR->title,BIGADDR->author,BIGADDR->id,\
            BIGADDR->publisher,BIGADDR->publish_date,BIGADDR->lend_date,BIGADDR->return_date);        

}
void headline_show(void)
{
    printf("书名|");
    printf("作者|");
    printf("编号|");
    printf("出版商|");
    printf("出版日期|");
    printf("借书日期|");
    printf("归还日期");
    printf("\n");
}
void books_show(PBOOK head)//显示所有图书
{
    headline_show();
    struct list_head *tmp;
    PBOOK BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,BOOK,K);
        book_show(BIGADDR);
    }

}


int save_txt(PBOOK head)
{
    FILE* fp=fopen("book.txt","w+");
    char buf[1024];
    struct list_head *tmp;
    PBOOK BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {

        BIGADDR = GetBig(tmp,BOOK,K);
        memset(buf,0,sizeof(buf));
        sprintf(buf,"%s|%s|%s|%s|%s|%s|%s\n",\
            BIGADDR->title,BIGADDR->author,BIGADDR->id,BIGADDR->publisher,BIGADDR->publish_date,BIGADDR->lend_date,BIGADDR->return_date);        
        fwrite(buf,1,strlen(buf),fp);

    }
    fclose(fp);   
    return 0;
}

int load_txt(PBOOK head)
{
    FILE* fp=fopen("book.txt","r");
    char buf[1024];
    struct list_head *tmp;
    PBOOK newbook;
    while(feof(fp)==0)
    {
        fgets(buf,1024,fp);
        printf("%s",buf);
      
        newbook=malloc(sizeof(BOOK));
        sscanf(buf,"%s|%s|%s|%s|%s|%s|%s\n",\
            newbook->title,newbook->author,newbook->id,newbook->publisher,newbook->publish_date,newbook->lend_date,newbook->return_date);        
        
        book_list_add(head,newbook);
        memset(buf,0,sizeof(buf));
    }
    fclose(fp);  

    return 0;
}


void book_add(PBOOK head)//图书信息添加
{
    PBOOK newbook=malloc(sizeof(BOOK));

    printf("输入书名:");
    scanf("%s",(newbook->title));
    printf("输入作者:");
    scanf("%s",(newbook->author));  
    printf("输入编号:");
    scanf("%s",(newbook->id));      
    
    printf("输入出版商:");
    scanf("%s",(newbook->publisher));
    printf("输入出版日期:");
    scanf("%s",(newbook->publish_date));

    printf("输入借书日期:");
    scanf("%s",(newbook->lend_date));
    printf("输入归还日期:");
    scanf("%s",(newbook->return_date));
    

    book_list_add(head,newbook);
    

}
void book_rand_add(PBOOK head)//从books和authors中随机添加图书信息
{
    int n=0;
    printf("Add how many books?\n");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        PBOOK newbook=malloc(sizeof(BOOK));
        strcpy(newbook->title,books[random()%10]);
        strcpy(newbook->author,authors[random()%10]);
        strcpy(newbook->publisher,"arcabaleno");
        strcpy(newbook->id,"88002233");    
        strcpy(newbook->publish_date,"2020-01-01");
        strcpy(newbook->lend_date,"2020-02-02");
        strcpy(newbook->return_date,"2020-03-03");
   
        book_list_add(head,newbook);
    }
    
}





int book_seek_by_title(PBOOK head,char title[ARRAY_SIZE],PBOOK record)//按书名查找
{
    struct list_head *tmp;
    PBOOK BIGADDR;
    int count=0;

    LIST_FOR_EACH(tmp,&head->K)
    {

        BIGADDR = GetBig(tmp,BOOK,K);
        if(strstr(BIGADDR->title,title))
        {
           
            PBOOK book=(PBOOK)malloc(sizeof(BOOK));
            memcpy(book,BIGADDR,sizeof(BOOK));//另外备份图书信息
            book_list_add(record,book);
            count++;
            
        }
    }

    return count;

}
int book_seek_by_author(PBOOK head,char author[ARRAY_SIZE],PBOOK record)//按作者查找
{
    struct list_head *tmp;
    PBOOK BIGADDR;
    int count=0;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,BOOK,K);
        if(strstr(BIGADDR->author,author))
        {
            PBOOK book=(PBOOK)malloc(sizeof(BOOK));
            memcpy(book,BIGADDR,sizeof(BOOK));//另外备份图书信息
            book_list_add(record,book);
            count++;
        }
    }

    return count;

}


void book_seek(PBOOK head)//图书检索
{
    char buf[ARRAY_SIZE];
    printf("Which book do you want to seek ? \n");
    scanf("%s",buf);
    PBOOK record=book_init();
    int n=0;
    n=book_seek_by_title(head,buf,record);
    if(n!=0)
    {
        printf("Find %d book(s) by title\n",n);
        books_show(record);
    }
    free(record);
    
    record=book_init();
    n=book_seek_by_author(head,buf,record);
    if(n!=0)
    {
        printf("Find %d book(s) by author\n",n);
        books_show(record);
    }
    free(record);
    

}

void book_del_by_title(PBOOK head,char title[ARRAY_SIZE])//按书名删除一本书
{
    struct list_head *tmp;
    PBOOK BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,BOOK,K);
        if(!strcasecmp(BIGADDR->title,title))
        {
            printf("%s will be del\n",BIGADDR->title);
            LIST_DEL(&BIGADDR->K);
            free(BIGADDR);
            break;
        }
    }
}


void book_del(PBOOK head)//图书删除
{
    char buf[ARRAY_SIZE];
    printf("Which book do you want to delete? \n");
    scanf("%s",buf);
    book_del_by_title(head,buf);
}

void book_change(PBOOK head)//图书修改
{
    char buf[ARRAY_SIZE];
    char oper;
    printf("Which book do you want to change? \n");
    scanf("%s",buf);

    struct list_head *tmp;
    PBOOK BIGADDR;
    LIST_FOR_EACH(tmp,&head->K)
    {
        BIGADDR = GetBig(tmp,BOOK,K);
        if(!strcasecmp(BIGADDR->title,buf))
        {
            printf("借书日期(l)\t归还日期(r)\n");
            scanf(" %c",&oper);
            switch(oper)
            {

                case 'l':
                    printf("借书日期:");
                    scanf("%s",BIGADDR->lend_date);

                    break;
                case 'r':
                    printf("归还日期:");
                    scanf("%s",BIGADDR->return_date);

                    break;
                default:
                    printf("输入正确操作符\n");
                    break;
            }
            books_show(BIGADDR);
            break;
        }
    }

}

void book_free(PBOOK head)//释放图书所有节点
{
    struct list_head *p,*q;
    PBOOK BIGADDR;

    LIST_FOR_EACH_SAFE(p,q,&(head->K))//q保存下一个需要释放的节点
    {
        BIGADDR = GetBig(p,BOOK,K);

        if(p!=&(head->K))
        {
            //printf("free:-->%s\n",BIGADDR->title);
        }
        free(BIGADDR);
    }
    BIGADDR = GetBig(p,BOOK,K);
    free(BIGADDR);
    free(head);
}

void book_info(PBOOK head)//图书信息
{

    char buf[ARRAY_SIZE]= {0};
    char oper;

    while(1)
    {
        
        printf("\n添加(a)\t修改(b)\t查看(c)\t删除(d)\t检索(e)\tsave(f)\tload(g)\t退出(q)\n");
        scanf(" %c",&oper);
        system("clear");
        if(oper=='q')
        {
            
            return;
        }
        else
        {
            
            switch(oper)
            {
                case 'a':
                        //book_add(head);
                        book_rand_add(head);
                    break;
                    
                case 'b':
                       
                        book_change(head);
                    break;
                    
                case 'c':
                    
                        books_show(head);
                    break;

                case 'd':
                        book_del(head);
                    break;
                    
                case 'e':
                        book_seek(head);
                    break;
                case 'f':
                        save_txt(head);
                    break;
                    
                case 'g':
                        load_txt(head);
                    break;                    
                default:
                        printf("重新输入正确操作符\n");
                    break;
            }
        }
    }


}


#endif
