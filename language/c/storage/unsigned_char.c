#include <stdio.h>
#include <stdlib.h>


int strlonger(char *s, char *t)
{
    return strlen(s) - strlen(t) > 0;
}


void test_unsigned_and_signed(void)
{
    printf("=======test         -1=======\n");
    //  如果是char, 那么系统认为最高位是符号位, 而int可能是16或者32位, 那么会对最高位进行扩展
    signed char c7_1 = 0x00ff; //int i7_1 = (int)c7_1;
    //  如果是unsigned char, 那么不会扩展.
    unsigned char c7_2 = 0x00ff; //int i7_2 = (int)c7_2;
    //  最高位若为0时, 二者没有区别, 若为1时，则有区别
    printf("signed   %08x, %d\n", c7_1, c7_1);
    printf("unsigned %08x, %d\n", c7_2, c7_2);


    printf("\n=======test high bit 1=======\n");
    //  最高位为1
    signed char cc1 = 0x80;
    unsigned char cc2 = 0x80;
    printf("signed   %08x, %d\n", cc1, cc1);
    printf("unsigned %08x, %d\n", cc2, cc2);

    printf("\n=======test high bit 0=======\n");
    //  最高位为0
    signed char cc3 = 0x7f;
    unsigned char cc4 = 0x7f;
    printf("signed   %08x, %d\n", cc3, cc3);
    printf("unsigned %08x, %d\n", cc4, cc4);
}



///
int main(void)
{
/*
    short int v = -12345;
    unsigned short uv = (unsigned short)v;
    printf("v = %d, uv = %u\n", v, uv);
*/
    test_unsigned_and_signed();
    printf("\n\n\n\n");
    printf("strlonger(\"123\", \"12\") = %d\n", strlonger("123", "12"));
    printf("strlonger(\"123\", \"123456\") = %d\n", strlonger("123", "123456"));

    return EXIT_SUCCESS;
}
