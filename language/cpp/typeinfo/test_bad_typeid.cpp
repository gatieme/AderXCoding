// expre_bad_typeid.cpp

#include <typeinfo>
#include <iostream>

using namespace std;

class A
{
public:
  // object for class needs vtable
  virtual ~A( );
};

int main()
{
    A* a = NULL;

    try
    {
        cout << typeid(*a).name() << endl; // Error condition
    }
    catch (bad_typeid)
    {
        cout << "Object is NULL" << endl;
    }

    return 0;
}
