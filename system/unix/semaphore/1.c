/*************************************************************************
    > File Name: 1.c
    > Author: gatieme
    > Created Time: Mon 28 Mar 2016 09:40:07 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>


#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

#define DEFINE_SEMAPHORE

int         number;             // 被保护的全局变量

sem_t       sem_id;

void* thread_one_fun(void *arg)
{
    printf("thread_one start...\n");

    while(1)
    {

#ifdef DEINE_SEMAPHOER
        ///  等待并锁定信号量
        sem_wait(&sem_id);
        printf("thread_one have the semaphore\n");
#endif

        number++;

        sleep(1);

        printf("thread_one : number = %d\n", number);

#ifdef DEINE_SEMAPHOER
        ///  释放信号量
        sem_post(&sem_id);
#endif
    }
    return NULL;
}

void* thread_two_fun(void *arg)
{
    printf("thread_two start...\n");
    while(1)
    {

#ifdef DEINE_SEMAPHOER
        sem_wait(&sem_id);
        printf("thread_two have the semaphore \n");
#endif
        number--;

        sleep(1);

        printf("thread_two : number = %d\n", number);

#ifdef DEINE_SEMAPHOER
        sem_post(&sem_id);
#endif
    }
    return NULL;
}


int main(int argc,char *argv[])
{
    pthread_t   id1, id2;

    number = 1;


    sem_init(&sem_id, 0, 1);

    pthread_create(&id1, NULL, thread_one_fun, NULL);
    pthread_create(&id2, NULL, thread_two_fun, NULL);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    printf("main...\n");


    return EXIT_SUCCESS;
}
