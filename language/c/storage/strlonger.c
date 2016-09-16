#include <stdio.h>
#include <stdlib.h>


int strlonger(char *s, char *t)
{
    return strlen(s) - strlen(t) > 0;
}


///
int main(void)
{
    printf("strlonger(\"123\", \"12\") = %d\n", strlonger("123", "12"));
    printf("strlonger(\"123\", \"123456\") = %d\n", strlonger("123", "123456"));

    return EXIT_SUCCESS;
}
