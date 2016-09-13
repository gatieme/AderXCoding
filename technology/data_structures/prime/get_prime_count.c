#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <time.h>

#define ST             7
#define MOVE           4
#define BLOCKSIZE      (30030 * 17 * 2) // 2 * 3 * 5 * 7 * 11 * 13 * 17 = 510510
#define MAXM           ((BLOCKSIZE >> MOVE) + 1)
#define SET_BIT(a, n)  a[n >> 3] |= (1 << (n & 7))

typedef unsigned int uint;
typedef unsigned char uchar;
static uint Prime[6800];
static uchar BaseTpl[MAXM * 2];
static uchar NumBit0[1 << 8];
static const uint MAXN = (-1u / 2);

static int sieve( )
{
    // bug : 9被误认为是素数
    int primes = 0;
    //printf("the %d th is %d\n", primes, 2);
    Prime[primes++] = 2;
    SET_BIT(BaseTpl, 2);
    const uint maxp = (1 << 16) + 1000;
    for (uint i = 3; i < maxp; i += 2)
    {
        if ((BaseTpl[i >> MOVE] & (1 << (i / 2 & 7))) == 0)
        {
            //printf("the %d th is %d\n", primes, i);
            //getchar( );
            Prime[primes++] = i;
            for (uint p = i * i / 2; p < maxp / 2; p += i)
                SET_BIT(BaseTpl, p);
        }
    }

    return primes;
}

static void initBit( )
{
    memset(BaseTpl, 0, sizeof(BaseTpl));
    for (int k = 1; k < ST; k++)
    for (int p = Prime[k] / 2; p < sizeof(BaseTpl) * 8; p += Prime[k])
        SET_BIT(BaseTpl, p);

    for (int i = 1; i < sizeof(NumBit0) / sizeof(NumBit0[0]); i++)
        NumBit0[i] = NumBit0[i >> 1] + (i & 1);
    for (int j = 0; j < sizeof(NumBit0) / sizeof(NumBit0[0]); j++)
        NumBit0[j] = 8 - NumBit0[j];
}

static void inline crossOutFactorMod6(uchar bitarray[], const uint start,const uint leng, uint factor)
{
    uint s2, s1 = factor - start % factor;
    s1 += factor - factor * (s1 % 2);
    if (start <= factor)
        s1 = factor * factor;

    const char skip[] = {0, 2, 1, 1, 0, 1};
    const char mrid = ((start + s1) / factor) % 6 - 1;
    s1 = s1 / 2 + skip[(int)mrid] * factor;
    s2 = s1 + skip[mrid + 1] * factor;

    for (factor += 2 * factor; s2 <= leng / 2; ) {
        SET_BIT(bitarray, s1); s1 += factor; //6k + 1
        SET_BIT(bitarray, s2); s2 += factor; //6k + 5
    }

    if (s1 <= leng / 2)
        SET_BIT(bitarray, s1);;
}

static int segmentedEratoSieve(uint start, int leng)
{
    uchar bitarray[MAXM + 32];
    memcpy(bitarray + start % BLOCKSIZE / 16, BaseTpl, (leng >> MOVE) + 1);
    if (start < 32)
    {
        *((short*)bitarray) = 0x3461; //0x 0011 0100 0110 0001
    }
    *((uint*)bitarray + (leng >> 6)) |= ~((1u << (leng / 2 & 31)) - 1);

    const int maxp = (int)sqrt((double)start + leng) + 1;
    for (int i = ST, p = Prime[i];
         p < maxp;
         p = Prime[++i])
    {
        crossOutFactorMod6(bitarray, start, leng, p);
    }
    int primes = 0;
    for (int k = 0; k <= leng >> MOVE; k++)
    {
        primes += NumBit0[bitarray[k]];
    }

    return primes;
}

int countPrimes(uint start, uint stop)
{
    int primes = 0;
    if (start <= 2 && stop >= 2)
        primes = 1;

    const int blocksize = BLOCKSIZE - 0;

    primes -= segmentedEratoSieve(start - start % blocksize, start % blocksize);
    for (uint i = start / blocksize; i < stop / blocksize; i++)
        primes += segmentedEratoSieve(i * blocksize, blocksize);
    primes += segmentedEratoSieve(stop - stop % blocksize, stop % blocksize + 1);

    return primes;
}

int main(int argc, char* argv[])
{
    clock_t tstart = clock();

    sieve();
    initBit();

    //uint start, stop;
    int primeCnt = countPrimes(0, MAXN);
    //printf("PI(%u) = %d, time use %lu ms\n", MAXN, primeCnt, clock() - tstart);

    return 0;
}
