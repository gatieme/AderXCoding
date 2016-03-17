#include <iostream>

class A
{
public :
    A()
    :m_a(100)
    {

    }
    int m_a;
};


class T
{
public :

    int m_a;

};

int main( )
{
    int a( );           //  函数声明
    A aa();             //  被当作函数声明


    //  A中定义了默认构造函数
    //  因此new A 与 new A()
    A *pa1 = new A;
    std::cout <<pa1->m_a <<std::endl;

    A *pa2 = new A();
    std::cout <<pa2->m_a <<std::endl;

    //  T中未定义默认构造函数
    T *pt1 = new T;
    std::cout <<pt1->m_a <<std::endl;   //  随机值

    T *pt2 = new T( );
    std::cout <<pt2->m_a <<std::endl;   //  数据被初始化
    return EXIT_SUCCESS;
}
