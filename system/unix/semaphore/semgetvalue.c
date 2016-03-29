#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>

union semun
{
    int             val;
    struct semid_ds *buf;
    unsigned short     *array;
};

int main(int argc,char *argv[])
{
    int     semid,nsems,i;
    struct semid_ds seminfo;
    unsigned short *ptr;
    union semun arg;

    if(argc != 2)
    {
        printf("usage: semgetvalues<pathname>");
        exit(0);
    }

    //打开已经存在的信号量
    semid = semget(ftok(argv[1], 0), 0, 0);
    arg.buf = &seminfo;

    //获取信号量集的属性，返回semid_ds结构
    semctl(semid, 0, IPC_STAT, arg);
    nsems = arg.buf->sem_nsems;     //信号量的数目

    ptr = calloc(nsems,sizeof(unsigned short));
    arg.array = ptr;

    //获取信号量的值
    semctl(semid, 0, GETALL, arg);
    for(i = 0; i < nsems; i++)
    {
        printf("semval[%d] = %d\n", i, ptr[i]);
    }

    return EXIT_SUCCESS;
}
