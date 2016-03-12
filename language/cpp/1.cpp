#include <iostream>
#include<iomanip>

#include <cstdio>
#include <cstdlib>

class Base
{
public :
	virtual void Test() const = 0;

};


class Derived //: virtual public Base
{
public :
	virtual void Test() const
	{
		std::cout <<"Test..." <<std::endl;
	}
protected :
	int a;       // 4
	int b;       // 4
};


int main(void)
{
    std::cout <<"sizeof pointer " <<std::setfill('0') <<std::setw(2) <<sizeof(char *) <<std::endl;
    std::cout <<"sizeof    Base " <<std::setfill('0') <<std::setw(2) <<sizeof(class Base) <<std::endl;
    std::cout <<"sizeof Derived " <<std::setfill('0') <<std::setw(2) <<sizeof(class Derived) <<std::endl;
	return EXIT_SUCCESS;
}
