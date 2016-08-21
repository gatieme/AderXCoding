
#include <stdio.h>
#include <stdlib.h>
//#include <avr/io.h>

// 使用指定的寄存器实现两个操作数相加
int AddReg(int a, int b);
// 不指定寄存器实现两个整数相加
int Add(int a, int b);

// Main Funciton
int main(void)
{
    printf("%d\n", AddReg(10, 15));     // 调用AddReg函数
    printf("%d\n", Add(10, 15));        // 调用Add函数


    int a = 10, b = 15, sum;            // 主函数内部直接潜入汇编代码
    /*asm(
        "add %%ebx, %%eax"
        : "=a"(sum)
        : "a"(a), "b"(b)
        : "memory"
     );
     printf("%d\n", sum);
    */
     return EXIT_SUCCESS;
}





// 使用指定的寄存器实现两个操作数相加
int AddReg(int a, int b)
{
    asm(
        "add %%ebx, %%eax"
        : "=a"(a)
        : "b"(b), "a"(a)
    );

    return a;
}

// 不指定寄存器实现两个整数相加
int Add(int a, int b)
{
    asm
    (
        //"lock;\n"
        "add %1,%0;\n"
        : "=m"(a)
        : "r"(b), "m"(a)
      //  :
    );

    return a;
}

