#include <iostream>




class Base
{
public :
    int     m_value;
    Base    *m_next;
};


void BaseFunc()
{
    Base base;


    std::cout <<base.m_value  <<", " <<base.m_value <<std::endl;
    if(base.m_value || base.m_next)
    {
        std::cout <<"..." <<std::endl;
    }
}

int main(void)
{
    BaseFunc();

}
