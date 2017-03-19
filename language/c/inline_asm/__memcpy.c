#include <stdio.h>
#include <stdlib.h>

#ifdef CONFIG_SMP
#define LOCK_PREFIX "lock;"
#else
#define LOCK_PREFIX ""
#endif

#ifdef CONFIG_X86_32
static void *__memcpy(void *dest, const void *src, size_t n)
{
        int d0, d1, d2;
        asm volatile(
                "rep ; movsl\n\t"
                "movl %4,%%ecx\n\t"
                "rep ; movsb\n\t"
                : "=&c" (d0), "=&D" (d1), "=&S" (d2)
                : "" (n >> 2), "g" (n & 3), "1" (dest), "2" (src)
                : "memory");

        return dest;
}
#else
static void *__memcpy(void *dest, const void *src, size_t n)
{
        long d0, d1, d2;
        __asm__ __volatile__
        (
                "rep ; movsq\n\t"
                "movq %4,%%rcx\n\t"
                "rep ; movsb\n\t"
                : "=&c" (d0), "=&D" (d1), "=&S" (d2)
                : "" (n >> 3), "g" (n & 7), "1" (dest), "2" (src)
                : "memory");

        return dest;
}
#endif


#if 0
static __inline__ void* __memcpy(void *to, const void *from, size_t n)
{
    int d0, d1, d2;
    (
        "rep; movsl\n\t"
        "testb $2, %b4\n\t"
        "je 1f\n\t"
        "movsw\n\t"
        "1:\ttestb $1, %b4\n\t"
        "je 2f\n\t"
        "movsb\n\t"
        : "=c" (d0), "=D" (d1), "=s" (d2)
        : "0" (n / 4), "q" (n), "1" ((long) to), "2" ((long) from)
        : "memory"
    );

    return (to);
}
#endif

#define SIZE 81
int main(void)
{
    char from[SIZE] = "Hello World\0";
    char to[SIZE] = "Gatieme\0";

    printf("%s %s\n", from, to);
    __memcpy(to, from, SIZE);
    printf("%s %s\n", from, to);


    return EXIT_SUCCESS;
}
