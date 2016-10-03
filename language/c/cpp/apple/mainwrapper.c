#include "applewrapper.h"
#include <assert.h>

int main(void)
{

    struct tagApple * pApple;

    pApple = GetInstance();

    SetColor(pApple, 1);

    int color = GetColor(pApple);

    printf("color = %d\n", color);
    ReleaseInstance(&pApple);
    assert(pApple == 0);
    return 0;
}
