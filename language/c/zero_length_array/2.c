#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a[0];
    char *b = NULL;

    printf("sizeof(a) = %d, address = %p %p\n", sizeof(a), &a, a);
    printf("sizeof(b) = %d, address = %p %p\n", sizeof(b), &b, b);
}
