/*************************************************************************
    > File Name: print.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: Sun 24 Jul 2016 10:18:52 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>


void test()
{

    int a = 0;
    printf("%d %d %d\n", a, a++, a);
    printf("%d %d %d\n", a++, a, a);
    printf("%d %d %d\n", a, a, a++);
}

int main(int argc, char *argv[])
{
    test( );
    return EXIT_SUCCESS;
}


