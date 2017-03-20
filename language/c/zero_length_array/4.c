// 4.c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a[0];
    char *b;

    printf("%d %d\n", sizeof(a), sizeof(b));
}