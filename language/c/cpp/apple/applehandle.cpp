#include "applehandle.h"
#include "apple.h"
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

static std::vector<Apple *> g_appleVector;

int GetInstance(int * handle)
{
    g_appleVector.push_back(new Apple( ));
    *handle = 0;
    return 1;
}
void ReleaseInstance(int *handle)
{
    Apple * papple = g_appleVector[*handle];
    g_appleVector.erase(g_appleVector.begin( ) + *handle);
    delete papple;
    *handle = -1;

}
void SetColor(int handle, int color)
{
    g_appleVector[handle]->SetColor(color);
}

int GetColor(int handle)
{
    return g_appleVector[handle]->GetColor();
}


#ifdef __cplusplus
}
#endif
