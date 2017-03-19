#include <stdio.h>
#include <stdlib.h>

#ifdef CONFIG_SMP
#define LOCK_PREFIX "lock;"
#else
#define LOCK_PREFIX ""
#endif


static __inline__ void set_bit(int nr, volatile void *addr)
{
#define ADDR (*(volatile long *) addr)
    __asm __volatile__
    (
        LOCK_PREFIX
        "btsl %1, %0;"
        : "=m" (ADDR)
        : "Ir" (nr)
    );
}


int main(void)
{
    long count = 0x00;

    printf("%0x\n", count);
    set_bit(2, &count);
    printf("%0x\n", count);

    return EXIT_SUCCESS;
}
