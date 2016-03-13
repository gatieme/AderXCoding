#include <iostream>


class X
{
};


class Y : public virtual X
{

};

class Z : public virtual X
{

};



class A : public Y, public Z
{

};


int main( )
{
    std::cout <<sizeof(X) <<std::endl;
    std::cout <<sizeof(Y) <<std::endl;
    std::cout <<sizeof(Z) <<std::endl;
    std::cout <<sizeof(A) <<std::endl;

    return 0;
}
