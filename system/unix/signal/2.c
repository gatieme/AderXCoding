/*************************************************************************
    > File Name: 2.c
    > Author: gatieme
    > Created Time: Sun 27 Mar 2016 02:57:57 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>



#include<stdlib.h>
#include<stdio.h>
int  main()
{
    char *endptr;
    char a[] = "12345.6789";
    char b[] = "1234.567qwer";
    char c[] = "-232.23e4";

    printf( "a=%lf\n", strtod(a, NULL) );
    printf( "b=%lf\n", strtod(b, &endptr) );
    printf( "endptr=%s\n", endptr );
    printf( "c=%lf\n", strtod(c, NULL) );
}
