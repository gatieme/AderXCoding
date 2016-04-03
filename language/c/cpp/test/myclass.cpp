/*************************************************************************
    > File Name: add.cpp
    > Author: gatieme
    > Created Time: Sun 03 Apr 2016 03:16:54 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;


class MyClass
{
public :
    //  function
    int add(int a, int b)
    {
        return (a + b);
    }

    //  use class
    virtual int func(int )
    {
        cout <<"virtual function in class" <<endl;
        return 0;
    }
};

#ifdef __cplusplus
extern "C"
{
#endif


/* extern "C" */int test_add(int a, int b)
{
    MyClass mc;
    return mc.add(a, b);
}



/* extern "C" */void* create_myclass( )
{
    return new MyClass( );
}

/* extern "C" */void destroy_myclass( void* thisC)
{
    delete static_cast<MyClass *>(thisC);
}

/*extern "C"*/int call_myclass_func(MyClass *thismc, int i)
{
    return static_cast<MyClass *>(thismc)->func(i);
}


#ifdef __cplusplus
}
#endif
