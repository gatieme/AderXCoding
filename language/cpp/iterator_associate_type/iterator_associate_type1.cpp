///c++11 条款1：理解模板类型推导
///http://blog.csdn.net/coolmeme/article/details/43986163
///http://blog.csdn.net/shinehoo/article/details/5722362
#include <iostream>

template <class Iter, class T>
void func_impl(Iter iter, T t)

{
    T tmp;              //  这里解决了问题, T就是迭代器所指之物的类型, 本例为int

    /// ...  这里做原来func应该做的全部工作
}




template<class Iter>
inline func(Iter iter)
{
    func_impl(iter, *iter);
}


int main( )
{
    int i;
    func(&i);
}
