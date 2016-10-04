#include "applehandle.h"
#include <assert.h>

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
