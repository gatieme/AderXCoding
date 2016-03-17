#include <iostream>

// http://blog.csdn.net/hazir/article/details/21413833
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

    int *p = new int();
    std::cout <<*p <<std::endl;


    // new[] and delete
    int *pint1 = new int[10];
    delete pint1;

    A *pa1 = new A[10];
    delete pa1;

    // new and delete[]
    int *pint2 = new int;
    delete[] pint2;

    A *pa2 = new A[10];
    delete[] pa2;

    return EXIT_SUCCESS;
}
