#include <iostream>

//                  http://blog.csdn.net/hazir/article/details/21413833
class A
{
public :
    A()
    {

    }
    int a;
};

int main( )
{
    A a;
    std::cout <<a.a <<std::endl;

    A *pa = new A();
    std::cout <<pa->a <<std::endl;
    return EXIT_SUCCESS;
}
