#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
//判断是否为目录
int is_dir(char *path)
{
    struct stat st;
    stat(path,&st);
    if(S_ISDIR(st.st_mode))
        return 1;
    else
        return 0;
}
//处理字符串的函数
int endwith(char *s,char c)
{
//判断字符串结尾是否为"/"
    if(s[strlen(s)-1]==c)
        return 1;
    else
        return 0;
}

char* str_contact(char *str1,char *str2)
{
    char* result;
    result=(char*)malloc(strlen(str1)+strlen(str2)+1);
    if(!result)
    {
        printf("字符串连接时，内存动态分配失败\n");
        exit(1);
    }
    strcat(result,str1);
    strcat(result,str2);
    return result;
}
//复制文件函数
void copyfile(char* source_path,char* destination_path)
{
    char buffer[1024];
    int in,out,size;
    int fd,fd1;
    fd=open(source_path,O_RDWR);
    if(fd==-1)
    {
        printf("打开文件失败\n");
        exit(1);
    }
    out=read(fd,buffer,1024);
    if(out==-1)
    {
        printf("读取失败\n");
        exit(1);
    }
    close(fd);
    size=strlen(buffer);
    fd1=open(destination_path,O_WRONLY|O_CREAT,S_IRWXU|S_IRWXG);
    if(fd1==-1)
    {
        printf("打开文件失败\n");
        exit(1);
    }
    in=write(fd1,buffer,size);
    if(in==-1)
    {
        printf("写入失败\n");
        exit(1);
    }
}
//复制文件夹函数
void copydir(char* source_path,char* destination_path)
{
    if(!opendir(destination_path))
    {
        //如果不存在就用mkdir函数来创建
        if(mkdir(destination_path,0777))
            printf("创建文件夹失败\n");
    }
    char *path;
    path=(char*)malloc(512);
    path=str_contact(path,source_path);
    struct dirent* filename;
    DIR* sn=opendir(path);
    while(filename=readdir(sn))
    {
        //遍历DIR指针指向的文件夹 ,也就是文件数组
        memset(path,0,sizeof(path));
        path=str_contact(path,source_path);
        char* file_source_path;
        file_source_path=(char*)malloc(512);
        if(!endwith(source_path,'/'))
        {
            file_source_path=str_contact(file_source_path,source_path);
            file_source_path=str_contact(source_path,"/");
        }
        else
        {
            file_source_path=str_contact(source_path,"/");
        }


        char* file_destination_path;
        file_destination_path=(char*)malloc(512);
        if(!endwith(destination_path,'/'))
        {
            file_destination_path=str_contact(file_destination_path,destination_path);
            file_destination_path=str_contact(destination_path,"/");
        }
        else
        {
            file_destination_path=str_contact(file_destination_path,destination_path);
        }


        //取文件名与当前文件夹拼接成一个完整路径
        file_source_path=str_contact(file_source_path,filename->d_name);
        file_destination_path=str_contact(file_destination_path,filename->d_name);
        if(is_dir(file_source_path))
        {
            if(!endwith(file_source_path,'.'))
            {
                copydir(file_source_path,file_destination_path);
            }
        }
        //否则按照单一文件的方法进行复制
        else
        {
            copyfile(file_source_path,file_destination_path);
            printf("复制%s到%s成功!\n",file_source_path,file_destination_path);
        }
    }


}

int main(int argc,char* argv[])
{
    if(argv[1]==NULL||argv[2]==NULL)
    {
        printf("请输入两个文件夹的路径，第一个为源文件的路径，第二个为目标文件夹的路径\n");
        exit(1);
    }
    char* source_path=argv[1];
    char* destination_path=argv[2];
    DIR* source=opendir(source_path);
    DIR* destination=opendir(destination_path);
    if(!source||!destination)
    {
        printf("你输入的第一个参数或者第二个参数不是文件夹\n");
    }
    copydir(source_path,destination_path);
    return 0;
}
