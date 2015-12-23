#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(void)
{
    /*FILE *fp = */freopen("input.txt", "w", stdout);

    srand(time(NULL));
    for(int i = 5000; i <=5000/* 10000*/; i += 5)
    {
        printf("%d\n", i);
        for(int j = 0; j < i; j++)
        {
            printf("%4d%4d\n", rand() % 100 + 1, rand() % 100 + 1);
        }
    }
    return 0;
}
