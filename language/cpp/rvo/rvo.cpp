#include <iostream>
using namespace std;


class Base
{
public :
	Base(int num)
	{
	    m_num = num;
	}
	Base(const Base &base)
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



Base GetBase( )
{
	Base base(10);
	cout <<"返回值是对象类型, 应该调用拷贝构造函数" <<endl;
	return base;
}

void GetBase(Base base)
{
	cout <<"参数是对象类型, 应该调用拷贝构造函数" <<endl;
}


int main( )
{
	Base b1(20);
	cout <<"使用一个类对象去初始化另一个类对象,　应该调用拷贝构造函数" <<endl;
	Base b2 = b1;
	//cout <<"使用一个可以隐式转换为Base类对象的整数值1来初始化, 应该调用拷贝构造函数" <<endl;
	//Base b3 = 1;
	b2 = GetBase( );
	GetBase( );
}
