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
    printf("0x");
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

    int num = 9;                                /* num是整型变量，设为9 */
    float* pFloat = (float *)&num;              /* pFloat表示num的内存地址，但是设为浮点数 */

    print_byte((void *)&num, sizeof(num));
    print_bit((void *)&num, sizeof(num));
    
    printf("the float : %f, %f\n",       num, *pFloat); //以浮点视角看
    printf("the int   : %d, %d\n",  (int)num, *pFloat); //以整型视角看
    

    *pFloat = 9.0f;                                /* 将num的值改为浮点数 */
    print_byte((void *)&num, sizeof(num));
    print_bit((void *)&num, sizeof(num));

    printf("the float : %f, %f\n",       num, *pFloat); //以浮点视角看
    printf("the int   : %d, %d\n",  (int)num, *pFloat); //以整型视角看
    

    return EXIT_SUCCESS;
}
