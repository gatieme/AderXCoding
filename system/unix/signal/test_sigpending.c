/*************************************************************************
      > File Name: test_sigpending.c
      > Author: GatieMe
      > Mail: gatieme@163.com
      > Created Time: 2016年03月27日 星期日 21时51分58秒
 ************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

void alrm_is_pending(const char *str)
{
    sigset_t pendingsigset;

    printf("%s: ", str);

    if (sigpending(&pendingsigset) < 0)
    {
        printf("sigpending error: %s\n", strerror(errno));
        exit(-1);
    }

    if (sigismember(&pendingsigset, SIGALRM))
    {
        printf("SIGALRM is pending\n");
    }
    else
    {
        printf("SIGALRM is not pending\n");
    }
}

int main(void)
{
    sigset_t sigset;

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGALRM);

    if (sigprocmask(SIG_BLOCK, &sigset, NULL) < 0)
    {
        printf("sigprocmask error: %s\n", strerror(errno));
        exit(-1);
    }

    alrm_is_pending("before alarm");

    alarm(2);
    sleep(4);

    alrm_is_pending("after alarm");

    return 0;

}
