/*************************************************************************
    > File Name: test_raise.c
    > Author: gatieme
    > Created Time: 2016年03月27日 星期日 12时16分15秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>


 int main(void)
{
    int i = 0;

    while(1)
    {
        i++;
        if(i == 3)
        {
            printf("I will raise SIGINT to myself...\n");
            raise(SIGINT);
        }
        printf("I am running now...\n");

        sleep(1);

    }

    return 0;

}
