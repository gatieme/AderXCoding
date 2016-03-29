#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>

//定义信号量操作共用体结构
union semun
{
    int                val;
    struct semid_ds    *buf;
    unsigned short     *array;
};

int main(int argc,char *argv[])
{
    int semid,nsems,i;
    struct semid_ds seminfo;
    unsigned short *ptr;
    union semun arg;

    if(argc < 2)
    {
            printf("usage: semsetvalues <pathname>[values ...]");
            exit(0);
    }

    //打开已经存在的信号量集合
    semid = semget(ftok(argv[1],0),0,0);
    arg.buf = &seminfo;

    //获取信号量集的相关信息
    semctl(semid,0,IPC_STAT,arg);
    nsems = arg.buf->sem_nsems;  //信号量的个数
    if(argc != nsems + 2 )
    {
        printf("%s semaphores in set,%d values specified",nsems,argc-2);
        exit(0);
    }

    //分配信号量
    ptr = calloc(nsems,sizeof(unsigned short));
    arg.array = ptr;

    //初始化信号量的值
    for(i=0;i<nsems;i++)
    {
        ptr[i] = atoi(argv[i+2]);
    }


    //通过arg设置信号量集合
    semctl(semid,0,SETALL,arg);

    return EXIT_SUCCESS;
}
