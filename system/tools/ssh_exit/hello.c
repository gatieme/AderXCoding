/*************************************************************************
    > File Name: hello.c
    > Author: gatieme
    > Created Time: 2016年04月08日 星期五 16时40分34秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>



int main(void)
{
    while(1)
    {
        printf("pid = %d, I am coming...\n", getpid( ));

        sleep(3);
    }

    return EXIT_SUCCESS;
}
