#include <stdio.h>
#include <stdlib.h>
#include <string.h>




void test_1(void)
{

    //// ==1==
    char buf1[4] = "hell"; printf("(%s)\n", buf1);
    char buf2[ ] = "hell"; printf("(%s)\n", buf2);
    char buf3[8] = { 0 }; memcpy(buf3, "hello", strlen("hell")); printf("(%s)\n", buf3);


    char buf4[4] = "hell"; strcpy(buf4, "hell"); printf("(%s)\n", buf4);
    char buf5[4] = "hell"; buf5[4] = '3';

}



void test_2(void)
{

    ////  ==2==
    enum digit{ ONE, TWO, THREE };
    enum color { RED = 2, BLACK };
    printf("%d, %d\n", ONE, BLACK);
}



void test_3( )
{
    //// ==3==
    #define ADD(arr, cnt)           \
    do                              \
    {                               \
        int i;                      \
        for(i = 0; i < cnt; i++)    \
        {                           \
            ret += arr[i];          \
        }                           \
    }while(0)                       \

    int arr[2][2] = {1, 1};
    int i, ret = 0;
    for(i = 0; i < 2; i++)
    {
        ADD(arr[i], 2);
    }
    printf("%d\n", ret);
}


void test_4(void)
{

    ////  ==4==
    struct { int a, b } t = { 1 };
    printf("%d", t.b);
    void func( ){ int a; printf("%d", a); }
    func( );
    printf("\n");

}


void test_5(void)
{


    ////  ==5==
    int i1 = 0xf0000000;
    unsigned int i2 = 0xf0000000;
    i1 >>= 1;
    i2 >>= 1;
    printf("%8x, %8x\n", i1, i2);

}


void test_6(void)
{

    ////  ==6==
    int i6_1 =3; i6_1 = !!i6_1;
    int i6_2 = -1; if(i6_2) i6_2 = 0; else i6_2 = 1;
    int i6_3 = 3 || 2 && 0;
    printf("%d %d %d\n", i6_1, i6_2, i6_3);

}


void test_7(void)
{


    ////  ==7==
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

void test_8(void)
{

    ////  ==8==
    printf("%d\n", sizeof("hello"));


}


void test_9(void)
{
    union uni
    {
        struct
        {
            int n3;
        }s1;
        struct
        {
            int n4;
            int n5;
        }s2;
    };

    union uni u;
    int *p = &u.s2.n4;
    memset(&u, 0, sizeof(u));
    u.s1.n3 = 1;
    u.s2.n4 = 2;
    u.s2.n5 = 3;
    *p = 4;
    printf("%d %d %d\n", u.s1.n3, u.s2.n4, u.s2.n5);
}


int main(void)
{
    test_9( );
    const char *str = "\x12\x34\x56\x78";
    printf("%x", *(int *)str);
}
