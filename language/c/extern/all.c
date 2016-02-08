#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int a;                  //  定义一个变量, 不初始化
    int b = 10;             //  定义一个变量, 同时进行初始化
    extern int  c;          //  声明一个外部extern的int型变量a

    printf("a = %d\n", a);
    printf("b = %d\n", b);
    printf("c = %d\n", c);

    extern int d = 10;


    return EXIT_SUCCESS;
}
