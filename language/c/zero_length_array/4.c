#include <stdio.h>
#include <stdlib.h>



void show()
{
    static char a[0];
    printf("%p\n", a);

    static char b[0];
    printf("%p\n", b);
}


int main(void)
{

    show( );

    return EXIT_SUCCESS;
}
