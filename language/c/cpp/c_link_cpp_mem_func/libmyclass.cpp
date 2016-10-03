#include <iostream>
using namespace std;

class MyClass;

#ifdef __cplusplus
extern "C"
{
#endif


/* extern "C" */int test_add(int a, int b)
{
    MyClass mc;

    return mc.add(a, b);
}




#ifdef __cplusplus
}
#endif
