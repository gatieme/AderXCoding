#include <iostream>
using namespace std;


class Base
{
public :
	Base(int num)
	{
        //cout <<"111" <<endl;
	    m_num = num;
	}

	Base(const Base &base)          //  复制构造函数...
	{
		cout <<"Copy constructor..." <<endl;
	}

	/*~Base( )
	{
		cout <<"Destroy...." <<endl;
	} */
private :
    int m_num;

};



Base RetBase( )
{
	Base base(10);
	//cout <<"返回值是对象类型, 应该调用拷贝构造函数" <<endl;


    // with RVO -=> 0 times
    // with `-fno-elide-constructors` -=> 1 times
    return base;
}

void ArgBase(Base base)
{
    // with RVO -=> 0 times
    // with `-fno-elide-constructors` -=> 1 times
	//cout <<"参数是对象类型, 应该调用拷贝构造函数" <<endl;
}

void InitBase()
{
    Base b1(20);
    //cout <<"使用一个类对象去初始化另一个类对象,　应该调用拷贝构造函数" <<endl;

    // with RVO -=> 0 times
    // with `-fno-elide-constructors` -=> 1 times
    Base b2 = b1;
}


int main( )
{

    cout <<"使用一个类对象去初始化另一个类对象,　应该调用拷贝构造函数" <<endl;
    InitBase();
    cout <<endl <<endl;

    cout <<"使用一个可以隐式转换为Base类对象的整数值1来初始化, 应该调用拷贝构造函数" <<endl;
	Base b1 = 1;
    cout <<endl <<endl;

	cout <<"返回值是对象类型, 应该调用拷贝构造函数" <<endl;
    RetBase( );
    cout <<endl <<endl;

	cout <<"返回值是对象类型, 同时用返回值去初始化一个类对象, 应该调用两次拷贝构造函数" <<endl;
    Base b2 = RetBase( );
    cout <<endl <<endl;


    cout <<"参数是对象类型, 应该调用拷贝构造函数" <<endl;
    ArgBase(b1);
    cout <<endl <<endl;
}

