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


int main(void)
{
    if(check_end() == 1)
    {
        printf("大端模式\n");
    }
    else
    {
        printf("小端模式\n");
    }

    int a = 1;
    print_bit((void *)&a, sizeof(a));

    int b = -1;
    print_bit((void *)&b, sizeof(b));

/*
X   = -00101011 = 0x0000002B 
[X]原= 10000000 00000000 00000000 00101011
[X]反= 11111111 11111111 11111111 11010100
[X]补= 11111111 11111111 11111111 11010101
[X]移=01010101
*/

    int x = 0x2B;
    print_bit((void *)&x, sizeof(x));
    int y = -0x2B;
    print_bit((void *)&y, sizeof(y));
    

    return EXIT_SUCCESS;
}
