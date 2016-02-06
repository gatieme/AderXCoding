
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void func1(void *args)
{
    while( 1 )
    {
        sleep(1);

        printf("I am PTHREAD_1 : hello world!\n");

    }
}

void func2(void *args)
{
    while( 1 )
    {
        sleep(2);

        printf("I am PTHREAD_2 : hello gatieme!\n");

    }
}
int main()
{
    pthread_t   pthread1, pthread2;


    //
    if(pthread_create(&pthread1, NULL, func1, (void *)NULL))
    {
        perror("error when create PTHREAD_1");
        return -1;
    }

    if(pthread_create(&pthread2, NULL, func2, (void*)NULL))
    {
        perror("error when create PTHREAD_2");
        return -1;
    }

    while(1)
    {
        //sleep(0);
    }
    return 0;
}

