#include <iostream>


class Concrete1
{
public :
    int     val = 0;
    char    bit1 = 'A';
    virtual void Print()
    {
        std::cout <<val <<bit1;
    }
};


class Concrete2 : public Concrete1
{
public :
    char    bit2 = 'B';
    virtual void Print()
    {
        std::cout <<val <<bit1 <<bit2;
    }
};

class Concrete3 :public Concrete2
{
public :
    char    bit3 = 'C';
    virtual void Print()
    {
        std::cout <<val <<bit1 <<bit2 <<bit3;
    }
};

int main()
{
    std::cout <<"sizeof(Concrete1) = "<<sizeof(Concrete1) <<std::endl;
    std::cout <<"sizeof(Concrete2) = "<<sizeof(Concrete2) <<std::endl;
    std::cout <<"sizeof(Concrete3) = "<<sizeof(Concrete3) <<std::endl;

    Concrete1 c1_1, c1_2;
    Concrete2 c2;
    Concrete3 c3;

    Concrete1 *pc1_1 = &c1_1, *pc1_2 = &c1_2;
    Concrete2 *pc2 = &c2;

    pc1_1 = pc2;
    *pc1_2 = *pc1_1;

    return 0;
}


