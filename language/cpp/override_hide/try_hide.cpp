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

    void f(int x)
    {

        Base::f(x);
    }

};


int main(void)
{

    //Derived *pd = new Derived;
    Derived d;
    d.f(10);

}
