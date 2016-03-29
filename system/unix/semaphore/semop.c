#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int main(int argc,char *argv[])
{
    int     c,i,flag,semid,nops;
    struct  sembuf *ptr;
    flag = 0;
        //根据命令行参数设置操作模式
    while( ( c = getopt(argc,argv,"nu")) != -1)
    {
        switch(c)
        {
            case 'n':
                flag |= IPC_NOWAIT;   //非阻塞
                break;
            case 'u':
                flag |= SEM_UNDO;   //不可恢复
                break;
        }
    }
    if(argc - optind < 2)
    {
        printf("usage: semops [-n] [-u] <pathname> operation...");
        exit(0);
    }
    //打开一个已经存在的信号量集合
    if((semid = semget(ftok(argv[optind],0),0,0)) == -1)
    {
        perror("semget() error");
        exit(-1);
    }
    optind++;  //指向当前第一个信号量的位置
    nops = argc - optind;   //信号量个数
    ptr = calloc(nops,sizeof(struct sembuf));
    for(i=0;i<nops;++i)
    {
        ptr[i].sem_num = i;  //信号量变换
        ptr[i].sem_op = atoi(argv[optind+i]);   //设置信号量的值
        ptr[i].sem_flg = flag;   //设置操作模式
    }
    //对信号量执行操作
    if(semop(semid,ptr,nops) == -1)
    {
        perror("semop() error");
        exit(-1);
    }

    return EXIT_SUCCESS;
}
