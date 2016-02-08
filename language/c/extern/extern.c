#include <stdio.h>
#include <stdlib.h>

//  是定义，定义了A为整型的外部变量
//  C中定义的变量默认就是extern的,
//  因此一般来说int a = 10 <==> extern int a = 10;
/*extern */int a = 10;


int main(void)
{
    extern int  a;           //  声明一个外部extern的int型变量a
    //  这是个声明而不是定义，声明A是一个已经定义了的外部变量
    //  注意：声明外部变量时可以把变量类型去掉如：extern a;
    printf("a = %d\n", a);



    return EXIT_SUCCESS;
}
