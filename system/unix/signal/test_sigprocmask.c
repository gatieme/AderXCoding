/*************************************************************************
      > File Name: test_sigprocmask.c
      > Author: GatieMe
      > Mail: gatieme@163.com
      > Created Time: 2016年03月27日 星期日 21时33分56秒
 ************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

static void sig_alrm(int signo)
{
      printf("received SIGALRM\n");
}

int main(void)
{
    sigset_t    sigset;

    //  初始化信号集
    sigemptyset(&sigset);

    //  添加一个闹钟信号
    sigaddset(&sigset, SIGALRM);

    //  屏蔽信号
    /*if (sigprocmask(SIG_BLOCK, &sigset, NULL) < 0)
    {
        printf("sigprocmask error: %s\n", strerror(errno));
        exit(-1);
    }
    else
    {
        printf("signal SIGALARM is BLOCK now...\n");
    }
*/
    if (signal(SIGALRM, sig_alrm) < 0)          //  添加信号处理函数
    {
        printf("signal error: %s\n", strerror(errno));
        exit(-1);
    }

    alarm(2);
    sleep(4);

    printf("before unblock sigprocmask...\n");
    //  取消屏蔽信号
    if (sigprocmask(SIG_UNBLOCK, &sigset, NULL) < 0)
    {
        printf("sigprocmask SIG_UNBLOCK error: %s\n", strerror(errno));
        exit(-1);
    }
    else
    {
        printf("signal SIGALARM is UNBLOCK now...\n");
    }

    return 0;
}


