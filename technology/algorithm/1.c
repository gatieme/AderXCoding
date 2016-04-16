#include <stdio.h>




int main(void)
{
    const int N = 5;

    int a[5]={2,1,3,1,4};

    int tmp1 = 0;

    int tmp2 = 0;

    for (int i=0; i<N; ++i)
    {
        tmp1+=(i+1);
        tmp2+=a[i];
    }

    printf("ÖØ¸´µÄÊý:%d\n",N-(tmp1-tmp2));

    return 0;
}
