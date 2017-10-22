/*************************************************************************
    > File Name: tmp.c
    > Author: GatieMe
    > Mail: gatieme@163.com
    > Created Time: Sun 22 Oct 2017 07:29:00 PM CST
 ************************************************************************/


#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    int i, total;
    total = 0;

    for (i = 0; i < 10; i++)
        total += i;

    if (total != 45)
        printf ("Failure\n");
    else
        printf ("Success\n");
    return 0;
}


