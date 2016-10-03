/*************************************************************************
    > File Name: main.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: Mon 03 Oct 2016 10:49:46 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "libmyclass.h"

int main( )
{

    printf("2 + 4 = %d\n", call_cpp_class_add(2, 4));

    return EXIT_SUCCESS;
}


