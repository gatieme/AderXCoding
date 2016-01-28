#include <stdio.h>
#include <stdlib.h>



//  函数指针
int (*func0)(int *p);                       //  一个指针, 指向一个带int*型参数的
int (*func1)(int *p, int (*f)(int*));
int (*func2[5])(int *p);
int (*(*func)[5])(int *p);
int (*(*func)(int *p))[5];
int (*(*func)[5][6])[7][8];
int (*(*(*func)(int *))[5])(int *);



int main(void)
{

    return EXIT_SUCCESS;
}
