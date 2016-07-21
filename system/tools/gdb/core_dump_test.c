/*************************************************************************
    > File Name: segmantfault.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: Tue 14 Jun 2016 05:25:24 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>


char *str = "hello world";

void core_test(void)
{
    str[0] = 'H';
}

int main(int argc, char *argv[])
{
    core_test();

    return EXIT_SUCCESS;
}


