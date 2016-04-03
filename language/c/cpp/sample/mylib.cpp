/*************************************************************************
    > File Name: mylib.cpp
    > Author: gatieme
    > Created Time: Sun 03 Apr 2016 02:50:10 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;


#include "sample.h"

/*
#ifndef __cplusplus
#define __cplusplus
    #include "mylib.h"
#endif
*/

#ifdef __cplusplus
    #include "mylib.h"
#endif

int myfunc( )
{
    sample ss;

    ss.function( );

    return 0;
}
