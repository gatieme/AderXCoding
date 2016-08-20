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

        for(j = 1;
            sqrt_i >= p_r[j] && i % p_r[j] != 0;
            ++j);

        if(sqrt_i < p_r[j])
        {
            p_r[count++] = i;
        }
    }
    return p_r[count - 1];
}

int main()
{
    for(int i = 1; i <= 10; i++)
    {
        cout <<"the" <<setw(3)<<i <<" th prime is " <<get_prime(i)<<endl;
    }

    return 0;
}
