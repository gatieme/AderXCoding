/*************************************************************************
    > File Name: test_sigset.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: 2016年03月27日 星期日 21时14分29秒
 ************************************************************************/

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

void handler(int sig)
{
    printf("Handle the signal %d\n", sig);
}

int main()
{
    sigset_t            sigset;         //  用于记录屏蔽字
    sigset_t            ign;            //  用于记录被阻塞的信号集
    struct sigaction    act;

    //清空信号集
    sigemptyset(&sigset);
    sigemptyset(&ign);

    //  向信号集中添加信号SIGINT
    sigaddset(&sigset, SIGINT);

    //  设置处理函数和信号集
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);

    printf("Wait the signal SIGINT...\n");
    pause();                            //挂起进程，等待信号

    //  设置进程屏蔽字，在本例中为屏蔽SIGINT
    sigprocmask(SIG_SETMASK, &sigset, 0);

    printf("Please press Ctrl+c in 10 seconds...\n");

    sleep(10);

    //  测试SIGINT是否被屏蔽
    sigpending(&ign);
    if(sigismember(&ign, SIGINT))
    {
        printf("The SIGINT signal has ignored\n");
    }

    //  在信号集中删除信号SIGINT
    sigdelset(&sigset, SIGINT);
    printf("Wait the signal SIGINT...\n");

    //  将进程的屏蔽字重新设置，即取消对SIGINT的屏蔽
    //  并挂起进程
    sigsuspend(&sigset);

    printf("The app will exit in 5 seconds!\n");

    sleep(5);

    return EXIT_SUCCESS;
}


