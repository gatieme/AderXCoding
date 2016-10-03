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
