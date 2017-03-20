#include <stdio.h>
#include <stdlib.h>

struct payload
{
    int   len;
    char  data[];
};

int main(void)
{
    struct payload pay;
    printf("%ld", sizeof(pay));
    return EXIT_SUCCESS;
}
