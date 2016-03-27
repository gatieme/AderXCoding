/*************************************************************************
    > File Name: test_alarm.c
    > Author: gatieme
    > Created Time: 2016年03月27日 星期日 12时31分15秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{

    if(alarm(3) < 0)
    {
    //  当调用该函数时，系统就启动了定时器，定时到3s后向当前进程发送一个SIGALRM信号.
    //  该信号默认情况下是终止当前进程.

        perror("alarm");
    }

    while(1)
    {

        sleep(1);

        printf("i am father process\n");

    }

    return 0;

}

