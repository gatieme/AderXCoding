#include <stdio.h>
#include <stdlib.h>


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
    
    printf("%d == %d\n", sizeof(float), sizeof(int));

    float f = 9.0f; //对于一块内存，按浮点型初始化
    int * pInt = (int *)(&f);
    print_byte((void *)&f, sizeof(f));
    print_bit((void *)&f, sizeof(f));

    printf("the float : %f, %f\n",      f, *pInt); //以浮点视角看
    printf("the int   : %d, %d, %d\n", f, (int)f, *pInt); //以整型视角看


    *pInt = 9;
    print_byte((void *)&f, sizeof(f));
    print_bit((void *)&f, sizeof(f));
    printf("the float : %f, %f\n",      f, *pInt); //以浮点视角看
    printf("the int   : %d, %d\n", (int)f, *pInt); //以整型视角看

    return EXIT_SUCCESS;
}
