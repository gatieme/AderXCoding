#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define DELAY_TIME 3

int main()
{

    pid_t   pid;

#ifdef DSEMAPHORE
    int     sem_id;
    key_t   sem_key;

    sem_key = ftok(".", 'a');

    //  以0666且create mode创建一个信号量，返回给sem_id
    sem_id = semget(sem_key, 1, 0666 | IPC_CREAT);

    //  将sem_id设为1, 即允许访问
    init_sem(sem_id, 1);

#endif

    if ((pid = fork( )) < 0)
    {
        perror("Fork error!\n");

        exit(1);
    }
    else if (pid == 0)      // 子进程
    {
        sleep(DELAY_TIME);
#ifdef DSEMAPHORE
        sem_p(sem_id); //    P操作
#endif

        printf("Child running...\n");
        sleep(DELAY_TIME);
        printf("Child %d,returned value:%d.\n", getpid(), pid);

#ifdef DSEMAPHORE
        sem_v(sem_id); //    V操作
#endif

        exit(0);

    }
    else
    {

#ifdef DSEMAPHORE
        sem_p(sem_id); //    P操作
#endif

        printf("Parent running!\n");
        sleep(DELAY_TIME);
        printf("Parent %d, returned value:%d.\n", getpid(), pid);

#ifdef DSEMAPHORE
        sem_v(sem_id); //    V操作

#endif

        waitpid(pid, 0, 0);

#ifdef DSEMAPHORE
        del_sem(sem_id);
#endif
        exit(0);
    }

    return EXIT_SUCCESS;
}
