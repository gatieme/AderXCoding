#include <iostream>
#include <cassert>

template<class class_type, class data_type1, class data_type2>
char* access_order(
                   data_type1 class_type::*mem1,
                   data_type2 class_type::*mem2)
{
    assert (mem1 != mem2);

    //return (void *)mem1 < (void *)mem2 ? "member 1 occurs first" : "member 2 occurs first";
    if(mem1 < mem2)
    {
        std::cout <<"member 1 occurs first" <<std::endl;
    }
    else
    {
        std::cout <<"member 2 occurs first" <<std::endl;
    }
}


class A
{
public :
    int a;
    int b;
};


int main(void)
{
    std::cout <<access_order(&A::a, &A::b) <<std::endl;

    return 0;
}


