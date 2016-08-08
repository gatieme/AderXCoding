
/*************************************************************************
> File Name: sort_l.c
> Author: SuooL
> Mail: 1020935219@qq.com
> Created Time: 2014年07月31日 星期五 15时44分32秒
************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>

#define NAME_SIZE 256

// 构建的链表节点数据结构
struct fnode
{
    struct fnode *next;     // 下一个成员
    char name[NAME_SIZE];   // 当前成员文件名
};

struct fnode *insert_list(struct fnode *temp,struct fnode *head)
{
    if(head==NULL)  //if linklist is empty,for temp is the first one
    {
        head=temp;
        return head;
    }

    if(strcmp(temp->name,head->name)<0) //temp will be insert before first one
    {
        temp->next=head;
        head=temp;
        return head;
    }

    struct fnode *next=head->next;
    struct fnode *prev=head;
    while(next!=NULL&& strcmp(temp->name,next->name)>0)
    {
        next=next->next;
        prev=prev->next;
    }
    temp->next=next;
    prev->next=temp;
    return head;
}

// 读取文件权限属性函数，根绝参数（lstat函数返回类型st_mode）列出各个文件的权限个类型字符
output_type_perm(mode_t mode)
{
    char  type[7]={'p','c','d','b','-','l','s'};
    int index=((mode>>12) & 0xF)/2;
    printf("%c",type[index]);

    char *perm[8]={"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};//rwx
    printf("%s",perm[mode>>6 &07]);
    printf("%s",perm[mode>>3 &07]);
    printf("%s",perm[mode>>0 &07]);
}

// 列出用户及组
void output_user_group(uid_t uid,gid_t gid)
{
    struct passwd *user;
    user=getpwuid(uid);
    printf("  %s",user->pw_name);

    struct group *group;
    group=getgrgid(gid);
    printf(" %s",group->gr_name);
}

// 列出个文件基本信息函数将各个函数的返回值输出的屏幕
output_mtime(time_t mytime)
{
    char buf[256];
    memset(buf,'\0',256);
    ctime_r(&mytime,buf);
    buf[strlen(buf)-1]='\0';
    //memcpy(buf,ctime(mytime),strlen(ctime(mytime))-1);
    printf("  %s",buf);
}

void output_info(struct fnode *head)
{
    struct fnode *temp=head;
    while(temp!=NULL)
    {
        struct stat mystat;
        if(-1==stat(temp->name,&mystat))
        {
            perror("stat");exit(EXIT_FAILURE);
        }
        output_type_perm(mystat.st_mode);
        printf("  %4d",mystat.st_nlink);
        output_user_group(mystat.st_uid,mystat.st_gid);
        printf(" %8ld",mystat.st_size);
        output_mtime(mystat.st_mtime);
        printf(" %s\n",temp->name);
        temp=temp->next;
    }

}
void free_list(struct fnode *ptr)
{
    struct fnode *temp=ptr;
    struct fnode *link=ptr;
    while(ptr)
    {
        temp=ptr;
        ptr=ptr->next;
        free(temp);
    }
}


// main（）函数源码
int main(int argc,char *argv[])
{
    if(argc < 2)
    {
        printf("usage :%s dir_name\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    int i;
    for(i=1;i<argc;i++)
    {
        struct fnode *linklist=NULL;


        struct stat stat_info;
        if(stat(argv[i],&stat_info)==-1)
        {
            perror("stat");exit(EXIT_FAILURE);
        }

        if (S_ISREG(stat_info.st_mode))     //regular file
        {
            struct fnode *temp=(struct fnode *)malloc(sizeof(struct fnode));
            if(NULL==temp)
            {
                perror("malloc");exit(EXIT_FAILURE);
            }
            temp->next=NULL;
            memset(temp->name,'\0',NAME_SIZE);
            memcpy(temp->name,argv[i],strlen(argv[i]));
            linklist=insert_list(temp,linklist);
            output_info(linklist);//output information of the file
        }
        else if(S_ISDIR(stat_info.st_mode))
        {
            char buf[NAME_SIZE];
            getcwd(buf,128);

            DIR  *dirp=NULL;
            dirp=opendir(argv[i]);
            if(NULL==dirp)
            {
                perror("opendir");exit(EXIT_FAILURE);
            }

            struct dirent *entp=NULL;
            while(entp=readdir(dirp))
            {
                struct fnode *temp=(struct fnode *)malloc(sizeof(struct fnode));
                if(NULL==temp)
                {
                    perror("malloc");exit(EXIT_FAILURE);
                }
                temp->next=NULL;
                memset(temp->name,'\0',NAME_SIZE);
                memcpy(temp->name,entp->d_name,strlen(entp->d_name));
                linklist=insert_list(temp,linklist);
            }
            chdir(argv[i]);//change the current dirctory
            close(dirp);
            output_info(linklist);
            chdir(buf);
        }
        free_list(linklist);
    }
    return 1;
}
