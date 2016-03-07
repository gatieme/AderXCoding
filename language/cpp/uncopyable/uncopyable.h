#include <iostream>

//  effective C++ 3rd
//  条款06 : 若不想使用编辑器自动生成的函数, 就应该明确决绝
//  类似于Boost提供的noncopyable 
class Uncopyable
{

protected :
private   :
	Uncopyable(const Uncopyable &);
	Uncopyable& operator=(const Uncopyable &);
};

/*
使用方法
class Base : private Uncopyable
{
};
*/