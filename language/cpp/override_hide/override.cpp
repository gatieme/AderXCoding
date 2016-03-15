#include <iostream>

class Base
{
public:

    void f(int x)
    {
        std::cout << "Base::f(int) " << x <<std::endl;
    }

    void f(float x)
    {
        std::cout << "Base::f(float) " << x <<std::endl;
    }

    virtual void g( )
    {
        std::cout << "Base::g(void)" <<std::endl;
    }

};



class Derived : public Base
{

public:

    virtual void g(void)
	{
    	std::cout << "Derived::g(void)" <<std::endl;
    }

};



int main(void)
{
	Derived d;

    Base *pb = &d;

    pb->f(42);        // Base::f(int) 42
    d.f(42);

    pb->f(3.1415926f);     // Base::f(float) 3.14
    d.f(3.1415926f);

    pb->g();          // Derived::g( )
    d.g();

    return 0;
}
