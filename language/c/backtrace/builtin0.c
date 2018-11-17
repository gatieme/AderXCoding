#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_LEVEL 4
void sigfunc(int signo)
{
    printf("%s(0): %p\n", __func__, __builtin_return_address(0));
    printf("%s(1): %p\n", __func__, __builtin_return_address(1));
    printf("%s(2): %p\n", __func__, __builtin_return_address(2));
    printf("%s(3): %p\n", __func__, __builtin_return_address(3));
    printf("%s(4): %p\n", __func__, __builtin_return_address(4));
    exit(1);
}

int b()
{
    printf("%s(0): %p\n", __func__, __builtin_return_address(0));
    while(1)
    {
        sleep(1);
    }
}

int a(int temp)
{
    temp += 1;
    printf("%s(0): %p\n", __func__, __builtin_return_address(0));

    b();

    return temp;
}

int c(int temp)
{
        temp++;

        printf("%s(0): %p\n", __func__, __builtin_return_address(0));

        a(123);

        return temp;
}

int main()
{
//    signal(SIGINT, sigfunc);
//    a(123);
    c(123);
    return 0;
}
