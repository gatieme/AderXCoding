#include <iostream>

#include "myclass.h"


using namespace std;


int MyClass::func(int i)
{
    cout <<"virtual function " <<i <<" in class" <<endl;

    return 0;
}
