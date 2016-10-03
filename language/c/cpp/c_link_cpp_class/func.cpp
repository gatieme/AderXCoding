/*************************************************************************
    > File Name: func.cpp
    > Author: gatieme
    > Created Time: Sun 03 Apr 2016 03:23:10 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;


//  cplusplus function
void function( )
{
    cout <<"cplusplus function" <<endl;
}

// the interface for c compiler
extern "C" void test_function(void)
{
    function( );
}



