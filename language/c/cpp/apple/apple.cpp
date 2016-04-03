/*************************************************************************
    > File Name: apple.cpp
    > Author: gatieme
    > Created Time: Sun 03 Apr 2016 03:57:36 PM CST
 ************************************************************************/

#include <iostream>
using namespace std;


#include "apple.h"

Apple::Apple()
: m_nColor(APPLE_COLOR_RED)
{

}

void Apple::SetColor(int color)
{
    this->m_nColor = color;
}

int Apple::GetColor(void)
{
    return this->m_nColor;
}
