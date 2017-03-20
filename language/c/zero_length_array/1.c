#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    char a[0];
    printf("%ld", sizeof(a));
    return EXIT_SUCCESS;
}