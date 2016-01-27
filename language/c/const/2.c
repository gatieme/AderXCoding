#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    //  The pointer itself is a constant，
    //  Point to cannot be modified，
    //  But point to a string can be modified
    char * const pstr = "abcd";  //  Pointer to a constant

    // I find that pstr(the address of "abcd") is in ReadOnly data
    // &pstr(the address of pstr) is in stack segment
    printf("%p  %p\n", pstr, &pstr);

    *(pstr + 2) = 'e';  //  segmentation fault (core dumped)
    printf("%c\n", *(pstr + 2));

    return EXIT_SUCCESS;
}



