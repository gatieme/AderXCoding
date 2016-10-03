#include <iostream>

#include "myclass.h"
#include "libmyclass.h"


using namespace std;



#ifdef __cplusplus
extern "C"
{
#endif


/* extern "C" */void* create_myclass( )
{
    return new MyClass( );
}

/* extern "C" */void destroy_myclass(void *thisC)
{
    delete static_cast<MyClass *>(thisC);
}

/*extern "C"*/int call_myclass_func(void *thismc, int i)
{
    return static_cast<MyClass *>(thismc)->func(i);
}


#ifdef __cplusplus
}
#endif
