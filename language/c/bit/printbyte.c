#include <stdio.h>
#include <stdlib.h>


int check_end()
{
    int   i = 0x12345678;
    char *c = (char *)&i; 

    return (*c == 0x12);
}


int CheckEnd()
{
    union
    {
        int a;
        char b;
    }u;

    u.a = 1;
    if (u.b == 1)
        return 0;
    else 
        return 1;
}

/*
addr  -=> 待打印的变量的首地址 
size  -=>·待打印的变量的大小 
return 成功返回打印的字节数  
*/
int print_all_byte(void *addr, int size)
{
    unsigned char *ptr = (unsigned char *)addr;
    int print_bytes = 0;
 
    if(ptr == NULL)
    {
        return -1; 
    }
 
    while(print_bytes < size)
    {
        printf("%02x", *ptr); 
        ptr++; 
        print_bytes++; 
    }
    printf("\n"); 
    return print_bytes; 
}
 
int main(void)
{
    if(check_end() == 1)
    {
        printf("大端\n");
    }
    else
    {
        printf("小端\n");
    }

    short shortvalue = 0x1234; 
    if(print_all_byte((void *)&shortvalue, sizeof(shortvalue)) != -1)
    {
        printf("print SHORT success!\n\n"); 
    }

    int intvalue = 0x12345678; 
    if(print_all_byte((void *)&intvalue, sizeof(intvalue)) != -1)
    {
        printf("print INT success!\n\n"); 
    }
 
    long longvalue = 0x87654321; 
    if(print_all_byte((void *)&longvalue, sizeof(longvalue)) != -1)
    {
        printf("print LONG success!\n\n"); 
    }
 
    float floatvalue = 0.12345678; 
    if(print_all_byte((void *)&floatvalue, sizeof(floatvalue)) != -1)
    {
        printf("printf FLOAT success!\n\n"); 
    }

    double doublevalue = 0.12345678; 
    if(print_all_byte((void *)&doublevalue, sizeof(doublevalue)) != -1)
    {
        printf("printf DOUBLE success!\n\n"); 
    }
 
    int array[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 1234}; 
    if(print_all_byte((void *)array, sizeof(array)) != -1)
    {
        printf("printf ARRAY success!\n\n"); 
    }


    return EXIT_SUCCESS; 
}