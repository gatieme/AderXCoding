/*************************************************************************
    > File Name: 1.c
    > Author: gatieme
    > Created Time: 2016年03月27日 星期日 14时01分51秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>


#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/*对信号SIGINT的响应函数*/
void sig_int(int sig)
{
        printf("Get signal: %d\n", sig);
}

int main()
{

    /*初始化sigaction 结构*/
    struct sigaction act;


    act.sa_handler = sig_int;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;


    sigaction(SIGINT, &act, 0);

    while(1)
    {
        printf("Hello World!\n");

        sleep(1);
    }
}
