// 4.c
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a[0] = (char *)malloc(sizeof(char) * 2);
    char *b = (char *)malloc(sizeof(char) * 2);

    printf("%d %d\n", sizeof(a), sizeof(b));
}