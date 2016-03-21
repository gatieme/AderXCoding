/*************************************************************************
    > File Name: 3typeif.cpp
    > Author: gatieme
    > Created Time: 2016年03月21日 星期一 16时31分59秒
 ************************************************************************/

#include <iostream>
#include <typeinfo>
using namespace std;



class A
{
};

int main( )
{
    int ia = 10;
    cout <<"typeid(int) = " <<typeid(ia).name() <<endl;
    if(typeid(ia) == typeid(int))
    {
        cout <<"int" <<endl;
    }

    cout <<"typeid(char) = " <<typeid(float).name( ) <<endl;

    cout <<"typeid(float) = " <<typeid(float).name() <<endl;

    cout <<"typeid(double) = " <<typeid(double).name() <<endl;

    cout <<"typeid(A) = " <<typeid(A).name() <<endl;


    return 0;
}
