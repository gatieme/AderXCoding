#include <stdio.h>
#include <stdlib.h>




extern int test_add(int a, int b);


int main(void)
{
    printf("2 + 4 = %d\n", test_add(2, 4));

    return 0;
}
