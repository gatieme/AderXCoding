#include <stdio.h>
#include <stdlib.h>

int check_end()
{
    int   i = 0x12345678;
    char *c = (char *)&i;

    return (*c == 0x12);
}

int print_bit(void *addr, int size)
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

    return print_bytes;
}

int print_byte(void *addr, int size)
{
    unsigned char *paddr = (unsigned char *)addr;
    int print_bytes = 0;

    if(paddr == NULL)
    {
        return -1;
    }

    while(print_bytes < size)
    {
        printf("%02x", *paddr);
        paddr++;
        print_bytes++;
    }
    printf("\n");
    return print_bytes;
}

void test_unsigned_and_signed(void)
{
    //  如果是char, 那么系统认为最高位是符号位, 而int可能是16或者32位, 那么会对最高位进行扩展
    signed char c7_1 = 0x00ff; //int i7_1 = (int)c7_1;
    //  如果是unsigned char, 那么不会扩展.
    unsigned char c7_2 = 0x00ff; //int i7_2 = (int)c7_2;
    //  最高位若为0时, 二者没有区别, 若为1时，则有区别
    printf("signed   %08x, %d\n", c7_1, c7_1);
    printf("unsigned %08x, %d\n", c7_2, c7_2);

    //  最高位为1
    signed char cc1 = 0x80;
    unsigned char cc2 = 0x80;
    printf("signed   %08x, %d\n", cc1, cc1);
    printf("unsigned %08x, %d\n", cc2, cc2);

    //  最高位为0
    signed char cc3 = 0x7f;
    unsigned char cc4 = 0x7f;
    printf("signed   %08x, %d\n", cc3, cc3);
    printf("unsigned %08x, %d\n", cc4, cc4);
}

int main(void)
{
    test_unsigned_and_signed();

    printf("%d\n", sizeof(long));
    unsigned char a = 336;
    print_bit((void *)&a, sizeof(char));
    print_bit((void *)&a, sizeof(short));
    printf("%d\n", a);

    int *p = &a;
    print_bit((void *)p, sizeof(int));
    printf("%d\n", *p);


    unsigned char b = -1;
    print_bit((void *)&b, sizeof(b));
    printf("%d\n", b);

    union A
    {
        short ia;
        unsigned char ca[2];
    }aa;
    aa.ia = 336;
    printf("%d %d\n", aa.ca[0], aa.ca[1]);

    aa.ca[0] = 336;
    printf("%d %d\n", aa.ca[0], aa.ca[1]);

    aa.ca[1] = 336;
    printf("%d %d\n", aa.ca[0], aa.ca[1]);

    return EXIT_SUCCESS;
}
