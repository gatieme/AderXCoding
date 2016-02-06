#include <stdio.h>
#include <stdlib.h>

int a = 10; //是定义，定义了A为整型的外部变量
int b = 10;

int main(void)
{
    extern int a;
    //这是个声明而不是定义，声明A是一个已经定义了的外部变量
    //注意：声明外部变量时可以把变量类型去掉如：extern A;

    printf("a = %d\n", a);

    extern b;
    printf("b = %d\n", b);

    return EXIT_SUCCESS;
}