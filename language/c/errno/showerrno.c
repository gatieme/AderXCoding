/*************************************************************************
    > File Name: 0.c
    > Author: GatieMe
    > Mail: ftcl@163.com
    > Created Time: Sat 23 Jan 2016 12:07:51 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char ** argv)
{
    int i = 0;
    for(i = 0; i < 256; i++)
    {
        printf("| %02d | %s |\n", i, strerror(i));
    }
    return 0;
}