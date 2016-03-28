/*************************************************************************
    > File Name: 1.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2016年03月28日 星期一 22时58分15秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int number;                 // 被保护的全局变量
sem_t sem_id1, sem_id2;



/*
 *  线程1,
 *  对sem_id1加锁(P操作)以后
 *  将number增加1
 *  同时对sem_id2进行释放，V操作
 *
 *  */
void* thread_one_fun(void *arg)
{
    sem_wait(&sem_id1);
    printf("thread_one have the semaphore\n");

    number++;

    printf("number = %d\n",number);
    sem_post(&sem_id2);

    return NULL;
}

/*
 *  线程2,
 *  对sem_id2加锁(P操作)以后
 *  将number减少1
 *  同时对sem_id1进行释放，V操作
 *
 *  */
void* thread_two_fun(void *arg)
{
    sem_wait(&sem_id2);
    printf("thread_two have the semaphore \n");

    number--;

    printf("number = %d\n",number);
    sem_post(&sem_id1);

    return NULL;
}

int main(int argc,char *argv[])
{
    number = 1;
    pthread_t id1, id2;

    /*
     *  由于程序初始时, sem_id1可进入, sem_id2不可进入
     *  两个线程的动作如下:
     *  thread one P(id1)  number++ V(id2)
     *  thread two P(id2)  number-- V(id1)
     *  而id1可进入, id2不可进入
     *  因此thread one先执行
     *  如果将id1与id2的顺序交换, 则执行顺序相反
     * */
    sem_init(&sem_id1, 0, 1);   // 空闲的
    sem_init(&sem_id2, 0, 0);   // 忙的

    pthread_create(&id1, NULL, thread_one_fun, NULL);
    pthread_create(&id2, NULL, thread_two_fun, NULL);

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    printf("main...\n");


    return EXIT_SUCCESS;
}
