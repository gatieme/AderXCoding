#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define SEM_R    0400   //用户（属主）读
#define SEM_A    0200   //用户（属主）写

#define SVSEM_MODE (SEM_R | SEM_A | SEM_R>>3 | SEM_R>>6)

int main(int argc,char *argv[])
{
    int   c, oflag, semid, nsems;

    oflag = SVSEM_MODE | IPC_CREAT;   //设置创建模式

    //根据命令行参数e判断是否制定了IPC_EXCL模式
    while((c = getopt(argc,argv,"e")) != -1)
    {
        switch(c)
        {
            case 'e':
                oflag |= IPC_EXCL;
                break;
        }
    }

    //判断命令行参数是否合法
    if (optind != argc -2)
    {
        printf("usage: semcreate [-e] <pathname> <nsems>");
        exit(-1);
    }

    //获取信号量集合中的信号量个数
    nsems = atoi(argv[optind+1]);

    //创建信号量，通过ftok函数创建一个key，返回信号量 标识符
    semid = semget(ftok(argv[optind],0),nsems,oflag);


    return EXIT_SUCCESS;
}
