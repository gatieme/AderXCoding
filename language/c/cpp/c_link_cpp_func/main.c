#include <stdio.h>
#include <stdlib.h>


int call_cpp_add(const int a, const int b);

int main( )
{
    printf("%d\n", call_cpp_add(2, 4));

    return 0;
}


