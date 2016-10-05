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

extern "C"
{
#endif

int myfunc( )
{
    sample ss;

    ss.function( );

    return 0;
}

#ifdef __cplusplus
}
#endif  //  #ifdef __cplusplus
