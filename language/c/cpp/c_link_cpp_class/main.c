#include <stdio.h>
#include <stdlib.h>

#include "libmyclass.h"

int main( )
{
    void *pclass = create_myclass( );
    call_myclass_func(pclass, 10);
    destroy_myclass(pclass);
    pclass = NULL;


    return EXIT_SUCCESS;
}


