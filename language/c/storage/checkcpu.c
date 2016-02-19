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

int main(void)
{
    short int   x;
    char        x0, x1;
    x = 0x1122;
    x0 = ((char *)&x)[0];  //低地址单元
    x1 = ((char *)&x)[1];  //高地址单元
    printf("x0 = 0x%x, x1 = 0x%x\n",x0,x1);
    if(x0 == 0x22 && x1 == 0x11)
    {
        printf("小端\n");
    }
    else
    {
        printf("大端\n");
    }

    if(check_end() == 1)
    {
        printf("大端\n");
    }
    else
    {
        printf("小端\n");
    }

    if(CheckEnd() == 1)
    {
        printf("大端\n");
    }
    else
    {
        printf("小端\n");
    }

    return EXIT_SUCCESS; 
}