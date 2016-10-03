/*************************************************************************
    > File Name: test.c
    > Author: gatieme
    > Created Time: Sun 03 Apr 2016 03:07:31 PM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define   SOFILE   "liblibmyclass.so"

int   (*f)();

int   main()

{

    void   *dp;

    dp=dlopen(SOFILE,RTLD_LAZY);

    f=dlsym(dp,"call_cpp_class_add");

    f();

    return   0;

}
