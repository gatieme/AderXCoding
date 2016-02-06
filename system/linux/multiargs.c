
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct ArgType
{
    int     m_count;
    char    m_message[81];
}ArgType;

void func(void *args)
{
    ArgType *pargs = (ArgType *)args;

    while( 1 )
    {
        sleep(1);

        printf("count = %d, message = %s\n", pargs->m_count++, pargs->m_message);

    }
}

int main()
{
    pthread_t   pthreadId;
    ArgType args = { 0, "Hello Pthread"};

    if(pthread_create(&pthreadId, NULL, func, (void*)&args) != 0)
    {
        perror("error when create PTHREAD");
        return -1;
    }

    while(1)
    {
        //sleep(0);
    }
    return 0;
}

