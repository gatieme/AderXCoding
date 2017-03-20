#include <stdio.h>
#include <stdlib.h>

int main(void)
{

    char a[0];
    printf("%p\n", a);

    char b[0];
    printf("%p\n", b);

    return EXIT_SUCCESS;
}