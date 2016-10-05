#include <iostream>
using namespace std;


#include "head.h"


A::A( )
{
}

A::~A( )
{
}

int A::gt( )
{
    this->m_s = 10;

    return 0;
}



int A::pt( )
{
    std::cout<<this->m_s<<std::endl;

    return 0;
}
