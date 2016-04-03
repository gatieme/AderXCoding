/*************************************************************************
    > File Name: add.cpp
    > Author: gatieme
    > Created Time: Sun 03 Apr 2016 03:03:59 PM CST
 ************************************************************************/

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
}

int A::pt( )
{
    std::cout<<this->m_s<<std::endl;
}
