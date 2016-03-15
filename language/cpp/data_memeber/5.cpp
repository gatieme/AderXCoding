#include <iostream>



class Point3d
{

public :
    virtual void Print( )
    {

    }
    int m_x;
    int m_y;
    int m_z;
};



int main(void)
{
    Point3d a;
    std::cout <<"sizeof(Point2d) = " <<sizeof(Point3d) <<std::endl;
    std::cout <<&a.m_z - &a.m_x <<std::endl;



    return 0;
}
