#include <semaphore.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

union semun
{
    int                 val;
    struct semid_ds     *buf;
    unsigned short      *array;
};

// 将信号量sem_id设置为init_value
int init_sem(int sem_id, int init_value)
{
    union semun     sem_union;
    sem_union.val = init_value;

    if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
    {
        perror("Sem init");

        exit(1);
    }

    return 0;
}

// 删除sem_id信号量
int del_sem(int sem_id)
{
    union semun sem_union;
    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
    {
        perror("Sem delete");

        exit(1);
    }
    return 0;
}


// 对sem_id执行p操作
int sem_p(int sem_id)
{
    struct sembuf   sem_buf;
    sem_buf.sem_num = 0;//信号量编号
    sem_buf.sem_op  = -1;//P操作
    sem_buf.sem_flg = SEM_UNDO;//系统退出前未释放信号量，系统自动释放

    if (semop(sem_id, &sem_buf, 1) == -1)
    {
        perror("Sem P operation");

        exit(1);
    }

    return 0;
}


// 对sem_id执行V操作
int sem_v(int sem_id)
{
    struct sembuf   sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op  = 1;//V操作
    sem_buf.sem_flg = SEM_UNDO;

    if (semop(sem_id, &sem_buf, 1) == -1)
    {
        perror("Sem V operation");

        exit(1);
    }

    return 0;
}
