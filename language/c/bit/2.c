#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
#include <winsock.h>


int print_bit(char *addr, int size)
{

    unsigned char *ptr = (unsigned char *)addr;
    int print_bytes = 0;

    if(ptr == NULL)
    {
        return -1;
    }

    for(print_bytes = 0;
        print_bytes < size;
        print_bytes++, ptr++)
    {
#ifdef DEBUG
        printf("byte %d, data = %02x -=>", print_bytes, *ptr);
#endif
        for(int print_bits = 7;
        print_bits >= 0;
        print_bits--)
        {
            printf("%d", ((*ptr >> print_bits) & 1));
        }
#ifdef DEBUG
        printf("\n");
#endif

    }
    printf("\n");
}


#define max(a, b) (((a) > (b)) ? (a) : (b))

int main(void)
{
    int max = htonl(INT_MAX), min = htonl(INT_MIN);
    assert(max + 1 == min);
    print_bit((char *)&max, sizeof(int));
    print_bit((char *)&min, sizeof(int));

//#define INT_MAX ((int)(~0U>>1))
//#define INT_MIN (-INT_MAX - 1)
//#define UINT_MAX (~0U)
//#define LONG_MAX ((long)(~0UL>>1))
//#define LONG_MIN (-LONG_MAX - 1)
//#define ULONG_MAX (~0UL)
//#define LLONG_MAX ((long long)(~0ULL>>1))
//#define LLONG_MIN (-LLONG_MAX - 1)
//#define ULLONG_MAX (~0ULL)
    printf("%d\n", ((int)(~0U>>1)));

    return EXIT_SUCCESS;
}
