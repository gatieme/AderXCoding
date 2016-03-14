#include <iostream>

class A
{
    explicit int a;
};

class B
{

};


class C : public A, public B
{

};


class D : virtual public A
{

};

class E : virtual public A, virtual public B
{

};


class F
{
public :
    int         a;
    static int  b;
};

int main(void)
{
    std::cout <<"sizeof(A) == "<<sizeof(A) <<std::endl;
    std::cout <<"sizeof(B) == "<<sizeof(B) <<std::endl;
    std::cout <<"sizeof(C) == "<<sizeof(C) <<std::endl;
    std::cout <<"sizeof(D) == "<<sizeof(D) <<std::endl;
    std::cout <<"sizeof(E) == "<<sizeof(D) <<std::endl;
    std::cout <<"sizeof(F) == "<<sizeof(D) <<std::endl;

    return 0;
}
