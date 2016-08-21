/*
 *  arm inline asm cookbook
 *  Demo Program
 *  Created on: 2014-6
 *  Author: Chris.Z
 */
#include <stdio.h>
#include <stdlib.h>


int value_convert(int x)
{
    int y;
    asm("mov %[result], %[value];"
    : [result] "=r" (y) /* Rotation result. */
    : [value]  "r"  (x) /* Rotated value.   */
    :                   /* No clobbers      */
    );

    return y;
}


int add(int x, int y)
{
    printf("x = %d, y = %d\n", x, y);

    asm("mov sub %[result], %[value], %]"
    : [result] "=r" (y) /* Rotation result. */
    : [value]  "r"  (x) /* Rotated value.   */
    :                   /* No clobbers      */
    );
    printf("x = %d, y = %d\n", x, y);
    return y;
}


int main()
{
    printf("GCC ARM Inline Assembler CookBook Demo!\n");

    int x = 3, y = 2;
    printf("call func value_convert with input x = %d,output : %d\n", x, value_convert(x));
    printf("call func add           with input x = %d, y = %d, output : %d\n", x, y, add(x, y));

    return 0;
}
