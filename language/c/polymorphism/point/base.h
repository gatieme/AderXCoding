//基类：base.h
 
#ifndef BASE_H
 
#define BASE_H
 
struct Base
{
	size_t size; //类所占空间
 
	void * (* ctor) (void * self, va_list * app); //构造函数
 
	void * (* dtor) (void * self); //析构函数
 
	void (* draw) (const void * self); //作图
};
 
#endif