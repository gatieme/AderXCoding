#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>


#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    } while(0)

void handler(int sig);

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_flags = 0;

    if (sigaction(SIGINT, &act, NULL) < 0)
        ERR_EXIT("sigaction error");

    struct sigaction act2;
    act2.sa_handler = handler;
    sigemptyset(&act2.sa_mask);
    act2.sa_flags = 0;

    if (sigaction(SIGQUIT, &act2, NULL) < 0)
        ERR_EXIT("sigaction error");

    for (;;)
        pause();
    return 0;
}

void handler(int sig)
{
    if(sig == SIGINT){

        printf("recv a SIGINT signal\n");
        sleep(5);
    }
    if (sig == SIGQUIT)
    {
        printf("recv a SIGQUIT signal\n");
    }
}