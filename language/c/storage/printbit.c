#include <stdio.h>
#include <stdlib.h>


//#define DEBUG
int isset(char data, int bit)
{ 
    data >>= bit;

    if(data & 1 == 0) 
    {
        return 0; 
    }
    else
    {
        return 1; 
    }
}

/*
addr  -=> 待打印的变量的首地址 
size  -=>·待打印的变量的大小 
return 成功返回打印的字节数  
*/
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
 
int main(void)
{
    /*short shortvalue = 0x1234; 
    if(print_bit((char *)&shortvalue, sizeof(shortvalue)) != -1)
    {
        printf("print SHORT success!\n\n"); 
    }*/

    int intvalue = 0x12345678;
    if(print_bit((char *)&intvalue, sizeof(intvalue)) != -1)
    {
        printf("print INT success!\n\n"); 
    }
 
    long longvalue = 0x87654321; 
    if(print_bit((char *)&longvalue, sizeof(longvalue)) != -1)
    {
        printf("print LONG success!\n\n"); 
    }
 
    float floatvalue = 0.12345678; 
    if(print_bit((char *)&floatvalue, sizeof(floatvalue)) != -1)
    {
        printf("printf FLOAT success!\n\n"); 
    }

    double doublevalue = 0.12345678; 
    if(print_bit((char *)&doublevalue, sizeof(doublevalue)) != -1)
    {
        printf("printf DOUBLE success!\n\n"); 
    }
 
    int array[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 1234}; 
    if(print_bit((char *)array, sizeof(array)) != -1)
    {
        printf("printf ARRAY success!\n\n"); 
    }


    return EXIT_SUCCESS; 
}