/*
指针常量和常量指针我们已经明白是怎么回事了，
当然我们今天说的不仅仅是这些，
因为我们还有一个神乎其神的东西：编译器。
语言也好，编译器也罢，语言的特性，
往往需要强大编译器的支持，
而编译器往往会在我们的代码中进行进一步的优化，
前面提到的RVO-编译器返回值优化 就是这么回事，
那么我们通过一个示例来看看，指针常量与常量指针更奇特的地方。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  依据右左法则
//
//  char * const cp; ( * 读成 pointer to )
//  cp is a const pointer to character
//  此时, const修饰指针变量cp，说明该指针是一个常量
//
//  const char * p;
//  p is a pointer to const character;
//  此时, const修饰的char *, 说明该指针指向的变量是一个常量
//
//  char const * p;
//  同上因为C++里面没有const*的运算符，所以const只能属于前面的类型。
//  C++标准规定，const关键字放在类型或变量名之前等价的。

// main function
int main(void)
{
    char *buf = "hello world";
    printf("栈区域地址%p  常量区%p\n\n", &buf, buf);

        //  字符串数组
    const char const str1[] = "abcd";
    const char const str2[] = "abcd";
    printf("[%p == %p] %d\n", &str1, &str2, &str1 == &str2);  //  栈区
    printf("[%p == %p] %d\n\n", str1, str2, str1 == str2);    // 栈区
    //strcpy(str1, "hello");
    printf("%s\n", str1);


    //  指向常量的指针, 指针本身的地址&p在栈中, 指向的地址p在常量区...
    const char * pstr1 = "abcd";
    const char * pstr2 = "abcd";
    printf("[%p == %p] %d\n", &pstr1, &pstr2, &pstr1 == &pstr2);    //  指针本身的地址在栈区
    printf("[%p == %p] %d\n\n", pstr1, pstr2, pstr1 == pstr2);      //  指针指向的地址在常量区
    //  指向常量的指针, 指针本身的指向可以修改
    pstr1 = "1234";
    pstr2 = "1234";
    printf("[%p == %p] %d\n", &pstr1, &pstr2, &pstr1 == &pstr2);    //
    printf("[%p == %p] %d\n\n", pstr1, pstr2, pstr1 == pstr2);

    pstr1 = "abcd";
    pstr2 = "1234";
    printf("[%p == %p] %d\n", &pstr1, &pstr2, &pstr1 == &pstr2);
    printf("[%p == %p] %d\n\n", pstr1, pstr2, pstr1 == pstr2);

    // 指针常量
    char * const pstr3 = "abcd";
    char * const pstr4 = "abcd";
    //pstr4 = "bcedf";          //  error, 此时指针的指向无法修改
    printf("[%p == %p] %d\n", &pstr3, &pstr4, &pstr3 == &pstr4);    // 指针作为局部常量存储在栈中 
    printf("[%p == %p] %d\n\n", pstr3, pstr4, pstr3 == pstr4);      // 字符串存储在常量区


    return EXIT_SUCCESS;
}