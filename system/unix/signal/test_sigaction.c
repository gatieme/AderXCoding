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


void handler(int sig);
/*
struct sigaction
{

    void     (*sa_handler)(int);
    //void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t  sa_mask;
    int       sa_flags;
    void     (*sa_restorer)(void);
};
*/

int main(int argc, char *argv[])
{
    struct sigaction    act;

    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    //因为不关心SIGINT上一次的struct sigaction所以，oact为NULL
    //与signal(handler,SIGINT)相同
    if (sigaction(SIGINT, &act, NULL) < 0)
    {
        perror("sigaction error\n");
    }

    for (;;)
    {
        pause( );
    }

    return 0;
}

void handler(int sig)
{
    printf("recv a sig = %d\n", sig);
}
