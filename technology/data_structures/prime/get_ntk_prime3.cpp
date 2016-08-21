//http://bbs.csdn.net/topics/390106185
#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

int get_prime(int n)
{
    int *p_r = new int[n];
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

int main()
{
    const int N = 10;
    cout <<"the " <<setw(3)<<N <<" th prime is " <<get_prime(N)<<endl;

    return 0;
}
