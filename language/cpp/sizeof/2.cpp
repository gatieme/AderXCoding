#include <iostream>

class AA
{

};

class A
{
virtual void fb(){}
};
class B: public A
{
};
class Bv: public virtual A, public virtual AA
{
    void fb()
    {
        std::cout <<"aaa" <<std::endl;
    }

};



int main(void)
{
    std::cout <<sizeof(A) <<std::endl;
    std::cout <<sizeof(B) <<std::endl;
    std::cout <<sizeof(Bv) <<std::endl;

    return 0;
}
