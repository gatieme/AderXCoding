#include <iostream>


class Base
{

public:

    void f(int x)
    {

    }

};

class Derived : public Base

{
public:

    void f(char *str)
    {

    }

};

int main(void)

{

    Derived *pd = new Derived;
    pd->f(10);          // error

    pd->Base::f(10);    // right

    Derived d;
    d.f(10);            // error
    d.Base.f(10);       // right


}
