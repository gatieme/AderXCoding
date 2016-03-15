#include <iostream>


class Point2d
{
public :
    int m_x;
    int m_y;

};



class Point3d : public virtual Point2d
{
public :
    int m_z;
};


class Vertex : public virtual Point2d
{
public :
    class Vertex *m_next;
};

class Vertex3d : public Point3d, public Vertex
{
public :
    float m_number;
};


int main(void)
{
    std::cout <<"sizeof(Point2d) = " <<sizeof(Point2d) <<std::endl;
    std::cout <<"sizeof(Point3d) = " <<sizeof(Point3d) <<std::endl;
    std::cout <<"sizeof(Vertex) = " <<sizeof(Vertex) <<std::endl;
    std::cout <<"sizeof(Vertex3d) = " <<sizeof(Vertex3d) <<std::endl;



    return 0;
}
