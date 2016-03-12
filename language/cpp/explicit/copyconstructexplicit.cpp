#include <iostream>

class Base
{
public :
    Base( )
    {
        //std::cout <<"default constructor..." <<std::endl;
        this->m_data = '\0';
    }

    explicit Base(char data)
    {
        //std::cout <<"simple constructor..." <<std::endl;
        this->m_data = data;
    }

    explicit Base(const Base &base)
    {
        std::cout <<"copy constructor..." <<std::endl;
        this->m_data = base.m_data;
    }

protected :

    char m_data;
};


//  参数为Base对象
void Func(const Base& base)     //  传入引用对象
{
}

//  返回值为base对象
Base& Func( )
{
    Base base;

    return base;            //  返回引用对象
}

void Copy()
{
    Base b1;
    Base b2(b1);            //  Base b2 = b1显示调用拷贝构造函数

}

int main(void)
{
    Base base(10);

    std::cout  <<std::endl <<"参数为Base对象..." <<std::endl;
    Func(base);     //  优化未优化情况下均调用1次拷贝构造函数

    std::cout  <<std::endl <<"返回值为base对象[可被优化]..." <<std::endl;
    Func();     //  优化情况下调用0次, 未优化情况下调用1次[函数返回时调用]

    //Base b(Func());     返回局部对象


    std::cout  <<std::endl <<"用base对象初始化另外一个对象..." <<std::endl;
    Copy();     //  优化未优化情况下均调用1次拷贝构造函数

    return 0;
}
