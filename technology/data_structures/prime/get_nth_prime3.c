//http://bbs.csdn.net/topics/390106185
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

long get_prime(int n)
{
    if(n <= 0)
    {
        return -1;
    }
    int p_r[n];
    int count = 1;
    int i, j;
    p_r[0] = 2;
    p_r[1] = 3;

    for(i = 3; count < n; i += 2)
    {
        int sqrt_i = sqrt(i);
        //printf("sqrt{%d) = %d\n", i, sqrt_i);

        //  已经得到的素数的倍数必然不是素数
        for(j = 1;
            sqrt_i >= p_r[j] && i % p_r[j] != 0;
            ++j)
        {
            /// NOP
            //printf("skip %d\n", j);
        }

        //printf("j = %d\n", j);
        if(sqrt_i < p_r[j])
        {
            p_r[count++] = i;
            //printf("%d is a primer\n", i);
        }
    }
    return p_r[count - 1];
}

int main(void)
{
    const int N = 10000;
    printf("the %d th prime is %ld\n", N, get_prime(N));

    getchar( );
    for(int i = 1; i < N; i++)
    {
        printf("the %d th prime is %ld\n", i, get_prime(i));
    }
    return 0;
}
