#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

bool is_prime(int num)
{
    if(num <= 1)
    {
        return false;
    }
    else if(num == 2 || num == 3)
    {
        return true;
    }
    int m;
    int k = sqrt(num);
    for(m = 2; m <= k; m++)
    {
        if(num % m == 0)
        {
            break;
        }
    }

    if(m > k)
    {
        //printf("%d is primer\n", num);
        return true;
    }
    else
    {
        //printf("%d is not primer\n", num);
        return false;
    }
}

long get_kth_primer(int K)
{
    int num, count;

    for(num = 1, count = 0; /*count <= K*/; num++)
    {
        if(is_prime(num) == true)
        {
            //printf("%d is primer\n", num);
            count++;
        }
        if(count == K)
        {
            break;
        }
    }

    //printf("the %d th prime is %ld\n", K, num);
    return num;
}


int main(void)
{

    for(int i = 1; i <= 10; i++)
    {
        printf("the %4d th prime is %ld\n", i, get_kth_primer(i));
    }


    return EXIT_SUCCESS;
}
