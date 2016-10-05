#include <stdio.h>
#include <stdlib.h>





extern int test_function(void);
extern int test_add(int a, int b);
extern void* create_myclass( );
extern void destroy_myclass( void* thisC);
extern int call_myclass_func(void *thismc, int i);



void c_function(int i)
{
    void *mc = create_myclass( );
    printf("%d", call_myclass_func(mc, i));
    destroy_myclass(mc);
}

int main(void)
{
    printf("2 + 4 = %d\n", test_add(2, 4));
    test_function( );
    c_function(2);

    return 0;
}
