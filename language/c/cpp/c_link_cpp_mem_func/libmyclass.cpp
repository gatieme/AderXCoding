#include <iostream>

#include "myclass.h"
#include "libmyclass.h"


using namespace std;



#ifdef __cplusplus
extern "C"
{
#endif


int call_cpp_class_add(int a, int b)
{
    MyClass mc;
    return mc.add(a, b);
}

#ifdef __cplusplus
}
#endif
