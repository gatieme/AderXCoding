//  http://blog.csdn.net/once_hnu/article/details/6302283
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>



//#define GET_PRIME_1
//#define GET_PRIME_2
#define GET_PRIME_3

#define MAX 1000000




#if  defined(GET_PRIME_1)

// 1：这是最原始的筛法，还有待优化
bool prime[MAX];
void get_prime( )
{
    prime[0] = prime[1] = 0;
    prime[2] = 1;
    for(int i = 3; i < MAX; i++)    //  偶数不是素数
    {
        prime[i] = ((i % 2 == 0) ? 0 : 1);
    }

    int t = (int)sqrt(MAX * 1.0);
    for(int i = 3; i <= t; i++)
    {
        if(prime[i] == true)    //  如果i是素数, 则i个倍数不是素数
        {
            for(int j = i * 2; j < MAX; j += i)
            {
                prime[j] = 0;
            }
        }
    }
}


#elif defined(GET_PRIME_2)

//2：优化后的筛法，手动地模拟原始筛法就可以发现，某个数字可能被不止一次地删去
//   优化后的筛法就可以避免这种不必要的删去操作
bool prime[MAX];
void get_prime( )
{
    prime[0] = prime[1] = 0;
    prime[2] = 1;

    for(int i = 3; i < MAX; i++)
    {
       prime[i] = ((i % 2 == 0) ? 0 : 1);
    }

    int t = (int)sqrt(MAX * 1.0);

    for(int i = 3; i <= t; i++)
    {
        if(prime[i] == true)
        {
            for(int j = i * i; j < MAX; j += 2*i)           //优化
            {
                prime[j] = 0;
            }
        }
    }
}

#else

//这就是素数的二次筛法，博士独创~~~~~
//与前两种筛法不同，此种筛法中prime[]=2*i+3
//即：我们只存储奇数，偶数肯定不是素数的）
bool prime[MAX>>1];
void get_prime()
{
    memset(prime, true, sizeof(prime));
    int n = MAX>>1, m = (int)(sqrt(MAX*1.0)/2.0);
    for(int i = 0; i <= m; i++)
    {
        if(prime[i])
        {
            for(int j = 2 * i * i + 6 * i + 3; j <= n; j += 2 * i + 3)
            {
                prime[j]=false;
            }
        }
    }
}

#endif


int main()
{
    int num;
    get_prime( );
    while(scanf("%d", &num) != EOF)
    {
        if(prime[num] == true)
        {
            printf("%d is prime\n", num);
        }
        else
        {
            printf("%d is not prime\n", num);
        }
    }

    return 0;
}
