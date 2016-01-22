#include <stdio.h>
#include <stdlib.h>


int main(void)
{


    char str1[] = "abcd";
    *(str1 + 2) = 'a';   // OK
    printf("%s\n", str1);

    char *pstr1 = str1;
    *(pstr1 + 2) = 'b'; // OK
    printf("%s\n", pstr1);

    char * const cpstr1 = str1;
    *(cpstr1 + 2) = 'c';    // OK
    printf("%s\n", cpstr1);

    char *pstr2 = "abcd";
    *(pstr2 + 2) = 'd';           //  segment fault
    printf("%s", pstr2);


    char * const cpstr2 = "abcd";  //  Pointer to a constant
    *(cpstr2 + 2) = 'e';  //  segmentation fault (core dumped)
    printf("%s\n", cpstr2);

    return EXIT_SUCCESS;
}