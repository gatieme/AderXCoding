/*************************************************************************
    > File Name: test_pause.c
    > Author: gatieme
    > Created Time: 2016年03月27日 星期日 12时51分32秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main(void)
{

    pid_t   pid;

    pid = fork();

    if(pid < 0)
    {
        perror("fork");
    }
    else if(pid == 0)
    {

        printf("I am child processm, I will PAUSE now\n");

        if(pause( ) < 0)
        {
            perror("pause");
        }

        while(1)
        {
            printf("hello i am child process\n");

            sleep(1);
        }
    }
    else
    {
        sleep(3);

        printf("i am a father process,i will send signal now\n");

        kill(pid, SIGINT);

    }

    return 0;
}
