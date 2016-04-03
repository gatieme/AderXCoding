#include "applehandle.h"
#include "apple.h"
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

static std::vector<Apple *> g_appleVector;

int GetInstance(int * handle)
{
    g_appleVector[0] =  new Apple;
    *handle = 0;
    return 1;
}
void ReleaseInstance(int *handle)
{
    delete g_appleVector[*handle];
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
};
#endif
