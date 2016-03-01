
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

static int value = 0;
pthread_mutex_t mutex;

void func(void *args)
{
    while( 1 )
    {
        pthread_mutex_lock(&mutex);

        sleep(1);

        value ++;
        printf("value = %d!\n", value);

        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t   pthread1, pthread2;

    pthread_mutex_init(&mutex, NULL);       //  创建互斥锁

    //
    if(pthread_create(&pthread1, NULL, func, (void *)NULL))
    {
        return -1;
    }

    if(pthread_create(&pthread2, NULL, func, (void*)NULL))
    {
        return -1;
    }

    while(1)
    {
        //sleep(0);
    }
    return 0;
}

