#include "applewrapper.h"
#include "apple.h"

#ifdef __cplusplus
extern "C" {
#endif
struct tagApple
{
    Apple apple;
};
struct tagApple *GetInstance(void)
{
    return new struct tagApple;
}
void ReleaseInstance(struct tagApple **ppInstance)
{
    delete *ppInstance;
    *ppInstance = 0;

}
void SetColor(struct tagApple *pApple, int color)
{
    pApple->apple.SetColor(color);
}

int GetColor(struct tagApple *pApple)
{
    return pApple->apple.GetColor();
}
#ifdef __cplusplus
}
#endif
