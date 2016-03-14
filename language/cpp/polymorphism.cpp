#include<iostream>
using namespace std;

class A
{
public:
    void foo()
    {
        std::cout <<"1" <<std::endl;
    }
    virtual void fun()
    {
        std::cout <<"2" <<std::endl;
    }
};
class B : public A
{
public:
    void foo()
    {
        std::cout <<"3" <<std::endl;
    }
    void fun()
    {
        std::cout <<"4" <<std::endl;
    }
};


class C : public A
{
public:
    void foo()
    {
        std::cout <<"5" <<std::endl;
    }
    void fun()
    {
        std::cout <<"6" <<std::endl;
    }
};


int main(void)
{
    A a;
    B b;
    C c;
    A *p = NULL;

    p = &a;
    p->foo();
    __vptr;

    p = &b;
    p->foo();
    p->fun();

    p = &c;
    p->foo();
    p->fun();

    A *arr[3] = {&a, &b, &c};
    for(int pos = 0; pos < 3; pos++)
    {
        arr[pos]->foo();
        arr[pos]->fun();
    }
    return 0;
}
