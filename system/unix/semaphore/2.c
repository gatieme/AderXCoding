//  http://blog.csdn.net/ljianhui/article/details/10813469

#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sem.h>

//线程函数
void    *thread_func(void *msg);
sem_t   sem;//信号量

#define MSG_SIZE 512

int main(void)
{
    int         res = -1;
    pthread_t   thread;
    void        *thread_result = NULL;
    char        msg[MSG_SIZE];

    //初始化信号量，其初值为0
    res = sem_init(&sem, 0, 0);

    if(res == -1)
    {
        perror("semaphore intitialization failed\n");
        exit(EXIT_FAILURE);
    }

    //创建线程，并把msg作为线程函数的参数
    res = pthread_create(&thread, NULL, thread_func, msg);

    if(res != 0)
    {
        perror("pthread_create failed\n");
        exit(EXIT_FAILURE);
    }

    //输入信息，以输入end结束，由于fgets会把回车（\n）也读入，所以判断时就变成了“end\n”
    printf("Input some text. Enter 'end'to finish...\n");
    while(strcmp("end\n", msg) != 0
       && strcmp("END\n", msg) != 0)
    {
        fgets(msg, MSG_SIZE, stdin);
        //把信号量加1
        sem_post(&sem);
    }

    printf("Waiting for thread to finish...\n");

    //等待子线程结束
    res = pthread_join(thread, &thread_result);
    if(res != 0)
    {
        perror("pthread_join failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined\n");
    //清理信号量
    sem_destroy(&sem);
    exit(EXIT_SUCCESS);
}

void* thread_func(void *msg)
{
    //把信号量减1
    sem_wait(&sem);

    char *ptr = msg;

    while(strcmp("end\n", msg) != 0
       && strcmp("END\n", msg) != 0)
    {
        int i = 0;
        //把小写字母变成大写
        for(; ptr[i] != '\0'; ++i)
        {
            if(ptr[i] >= 'a' && ptr[i] <= 'z')
            {
                ptr[i] -= 'a' - 'A';
            }
        }

        printf("You input %d characters\n", i-1);
        printf("To Uppercase: %s\n", ptr);

        //把信号量减1
        sem_wait(&sem);
    }

    //退出线程
    pthread_exit(NULL);
}
