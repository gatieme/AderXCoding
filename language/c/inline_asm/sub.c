#include <stdio.h>
#include <stdlib.h>
//#include <avr/io.h>

// 使用指定的寄存器两个参数相减
int SubReg(int a, int b);

// 不指定寄存器实现两个参数相减
int Sub(int a, int b);




int main(void)
{

     printf("%d\n", SubReg(100, 10));       // 调用SubReg
     printf("%d\n", Sub(100, 10));          // 调用Sub

     int a = 100, b = 10, sub;
     __asm__ __volatile__
    (
        "subl %%ebx, %%eax"
        : "=a"(sub)
        : "b"(b), "a"(a)
//        : "%ebx", "%eax"
    );
    printf("%d\n", sub);

    //system("PAUSE");
    return 0;
}



// 使用指定的寄存器两个参数相减
int SubReg(int a, int b)
{
    __asm__ __volatile__
    (
        "subl %%ebx, %%eax;"
        : "=a"(a)
        : "b"(b), "a"(a)
//        :
    );

    return a;
}

// 不指定寄存器实现两个参数相减
int Sub(int a, int b)
{
    __asm__ __volatile__
    (
        "subl %1, %0;"
        : "=m"(a)
        : "r"(b), "m"(a)
 //       :
    );

    return a;
}

