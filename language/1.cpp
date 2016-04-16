#include <iostream>
#include <vector>
#include <cmath>

class X
{
public :
    virtual void Print()
    {
        std::cout <<"X" <<std::endl;
    }
};


class A : public X
{
public :
    virtual void Print()
    {
        std::cout <<"A" <<std::endl;
    }
};


class B : public X
{
public :
    virtual void Print()
    {
        std::cout <<"B" <<std::endl;
    }
};


class D : public A
{
public :
    virtual void Print()
    {
        std::cout <<"D" <<std::endl;
    }
};

class E : public B
{
public :
    virtual void Print()
    {
        std::cout <<"E" <<std::endl;
    }
};

int main(void)
{
    auto fn = [](unsigned char a)
    {

        std::cout << std::hex << (int)a << std::endl;
    };
    fn(-1);

    long long i  =  pow(10,4932);
    if(i == i -  1)
        std::cout<<"they are the same";
    else
        std::cout<<"they are not the same";

//    std::vector<X*> vec;

//    X x;
//    A a;
//    B b;
//    D d;
//    E e;
//
//    vec.push_back(&x);
//    vec.push_back(&a);
//    vec.push_back(&b);
//    vec.push_back(&d);
//    vec.push_back(&e);
//
//    for(std::vector<X *>::iterator ite = vec.begin();
//    ite != vec.end();
//    ite++)
//    {
//        B *b = dynamic_cast<B *>(*ite);
//        //b->Print();
//    }


}
