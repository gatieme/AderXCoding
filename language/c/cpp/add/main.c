#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define   SOFILE   "sec.so"

//int   (*f)();

int   main()

{
/*
    void   *dp;

    dp=dlopen(SOFILE,RTLD_LAZY);

    f=dlsym(dp,"f");

    f();
*/
    f( );
    return   0;

}
