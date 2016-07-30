//  http://blog.csdn.net/Y_23k_bug/article/details/9904343

#include "stdio.h"
#include "stdlib.h"
#include "signal.h"
#include "sys/types.h"
#include "unistd.h"
#include "errno.h"
#include "string.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "dirent.h"
const char *PROC="/proc/";
typedef struct dirent DIRENT;
int get_info(char *what,char *file,char *filename)
{
    int fd,i=0;
    char filepath[50];
    strcpy(filepath,PROC);
    strcat(filepath,filename);
    strcat(filepath,file);
    if((fd=open(filepath,O_RDONLY))==-1)
        {
                printf("Open File %s Error:%s\n",filepath,strerror(errno));
                return 1;
        }
        while(read(fd,&what[i],sizeof(char)))
    {
        if(what[i]=='\n')
            break;
        i++;
    }
        what[i]='\0';
        close(fd);
    return 0;
}
void read_file(char *filename)
{
    char comm[50],cmd[300];
    int pid;
    get_info(comm,"/comm",filename);
    get_info(cmd,"/cmdline",filename);
    printf("Pid:%-8sName:%-16sPath:%s\n",filename,comm,cmd);
}
void display_info(void)
{
    DIR *dir;
    long i=0;
    DIRENT *dirp;
    if((dir=opendir(PROC))==NULL)
    {
        printf("Open Dir %s Error:%s\n",PROC,strerror(errno));
        exit(1);
    }
    while((dirp=readdir(dir))!=NULL)
    {
        if(strcmp(dirp->d_name,"1")==0)
            break;
        i++;
    }
    seekdir(dir,i);
    while((dirp=readdir(dir))!=NULL)
        read_file(dirp->d_name);
    closedir(dir);
}
void killbypid(char *pid_s)
{
    int pid;
    pid=atoi(pid_s);
    if(kill(pid,SIGKILL)==-1)
    {
        printf("Kill %s Error:%s\n",pid_s,strerror(errno));
        exit(1);
    }
}
int get_pid(char *filename,int *pid)
{
    DIR *dir;
    char comm[50];
    DIRENT *dirp;
    int flags=0,i=0;
    if((dir=opendir(PROC))==NULL)
    {
        printf("Open %s Error %s\n",PROC,strerror(errno));
        exit(1);
    }
    while((dirp=readdir(dir))!=NULL)
    {
        if(strcmp(dirp->d_name,"1")==0)
            break;
        i++;
    }
    seekdir(dir,i);
    while((dirp=readdir(dir))!=NULL)
    {
        get_info(comm,"/comm",dirp->d_name);
        if(strcmp(comm,filename)==0)
        {
            if(pid==NULL)
            {
                printf("%s Pid is:%s\n",filename,dirp->d_name);
                continue;
            }
            else
                *pid=atoi(dirp->d_name);
            flags=1;
            closedir(dir);
            return 1;
        }
    }
    if(flags==0)
    {
        printf("Cannot Find %s\n",filename);
        exit(1);
    }
    return 0;
}
void killbyname(char *filename)
{
    int pid;
    while(get_pid(filename,&pid))
    {
        printf("%s\t%d\n",filename,pid);
        if(kill(pid,SIGKILL)==-1)
        {
            printf("Kill %s Error:%s\n",filename,strerror(errno));
            exit(1);
        }
    }
}
void help(void)
{
    printf("\t\t   *****************my_kill*****************\n");
    printf("\t\t   *  -p:使用pid来结束进程               *\n");
    printf("\t\t   *  -n:使用进程名称来结束进程      *\n");
    printf("\t\t   *  -l:查看指定进程名的pid             *\n");
    printf("\t\t   *  -h:帮助                                      *\n");
    printf("\t\t   *  -L:查看指定pid的进程执行路径  *\n");
    printf("\t\t   *  无参数时显示当前系统所有进程*\n");
    printf("\t\t   *****************my_kill*****************\n");
}
void get_pid_in_path(char *filename)
{
    char cmd[300];
    if(get_info(cmd,"/cmdline",filename)==0)
        printf("The Pid %s Path is %s\n",filename,cmd);
}
int main(int argc,char **argv)
{
    if(argc==1)
        display_info();
    else if((strcmp(argv[1],"-p")==0)&&argc==3)
        killbypid(argv[2]);
    else if((strcmp(argv[1],"-n")==0)&&argc==3)
        killbyname(argv[2]);
    else if((strcmp(argv[1],"-l")==0)&&argc==3)
        while(get_pid(argv[2],NULL));
    else if((strcmp(argv[1],"-h")==0)&&argc==2)
        help();
    else if((strcmp(argv[1],"-L")==0)&&argc==3)
        get_pid_in_path(argv[2]);
    else
        printf("参数错误!\n");
    return 0;
}
//  get_pid函数写得比较蛋痛,请原谅我没有太注意格式
