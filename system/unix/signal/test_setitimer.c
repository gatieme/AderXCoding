/*************************************************************************
    > File Name: test_setitimer.c
    > Author: gatieme
    > Created Time: 2016年03月27日 星期日 12时45分15秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

int sec;
void sigroutine(int signo)
{
    switch (signo)
    {
        case SIGALRM :
        {
            printf("Catch a signal -- SIGALRM \n");
            signal(SIGALRM, sigroutine);
            break;
        }
        case SIGVTALRM:
        {
            printf("Catch a signal -- SIGVTALRM \n");
            signal(SIGVTALRM, sigroutine);
            break;
        }
    }
    fflush(stdout);
    return;
}

int main()
{
    struct itimerval value, ovalue, value2; //(1)
    sec = 5;

    printf("process id is %d\n", getpid());

    signal(SIGALRM, sigroutine);

    //signal(SIGVTALRM, sigroutine);

    value.it_value.tv_sec = 1;
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 1;
    value.it_interval.tv_usec = 0;

    ///  设置绝对时间
    setitimer(ITIMER_REAL, &value, &ovalue); //(2)

    value2.it_value.tv_sec = 0;
    value2.it_value.tv_usec = 500000;
    value2.it_interval.tv_sec = 0;
    value2.it_interval.tv_usec = 500000;

    ///  设置相对时间
    setitimer(ITIMER_VIRTUAL, &value2, &ovalue);

    while( 1 )
    {
        /// NOP;
    }
}
