/*************************************************************************
    > File Name: args_test.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: Tue 14 Jun 2016 11:08:59 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
    printf("argc count %d\n", argc);
    for(int pos = 0; pos < argc; pos++)
    {
        printf("args[%d] = %s\n", pos, argv[pos]);
    }

    return EXIT_SUCCESS;
}


