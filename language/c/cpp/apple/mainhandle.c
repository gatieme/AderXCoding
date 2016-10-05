#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "applehandle.h"

int main(void)
{
    int handle;

    GetInstance(&handle);

    SetColor(handle, 1);

    int color = GetColor(handle);

    printf("color = %d\n", color);
    ReleaseInstance(&handle);
    return 0;
}
