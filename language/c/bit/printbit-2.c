#include <stdio.h>
#include <stdlib.h>

/*
BE big-endian 大端模式,
最直观的字节序
地址低位存储值的高位,地址高位存储值的低位,
不需要考虑对应关系，只需要把内存地址从左到右按照由低到高的顺序写出，
把值按照通常的高位到低位的顺序写出,
两者对照，一个字节一个字节的填充进去

LE little-endian 小端模式,
最符合人的思维的字节序,
地址低位存储值的低位,地址高位存储值的高位,
怎么讲是最符合人的思维的字节序,
是因为从人的第一观感来说, 低位值小,
就应该放在内存地址小的地方也即内存地址低位
反之，高位值就应该放在内存地址大的地方，也即内存地址高位。
*/


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
