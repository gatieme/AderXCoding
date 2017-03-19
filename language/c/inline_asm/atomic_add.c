#include <stdio.h>
#include <stdlib.h>


static __inline__ int atomic_add(int count, int i)
{
    __asm __volatile__
    (
        "lock;"
        "addl %1, %0;"
        : "=m" (count)
        : "ir" (i), "m" (count)
    );
    return count;
}


int main(void)
{
    int count = 1;
    printf("%d", atomic_add(count, 5));

    return EXIT_SUCCESS;
}
