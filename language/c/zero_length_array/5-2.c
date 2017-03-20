#include <stdio.h>
#include <stdlib.h>




int main(void)
{

    const char *a = "Hello";
    printf("%p\n", a);

    const char *b = "Hello";
    printf("%p\n", b);

    const char c[] = "Hello";
    printf("%p\n", c);

    return EXIT_SUCCESS;
}
