///c++11 条款1：理解模板类型推导
///http://blog.csdn.net/coolmeme/article/details/43986163
///http://blog.csdn.net/shinehoo/article/details/5722362
///  STL源码剖析 PDF-119/534

#include <iostream>
template <class T>
struct MyIter
{
    MyIter(T *p = NULL)
    :m_ptr(p)
    {
        /// NOP...
    }

    T& operator*( ) const
    {
        return *m_ptr;
    }



    typedef T value_type;       //  内嵌型别声明{nested type}
    T   *m_ptr;
};


template <class Iter>
typename Iter::value_type          ///  这一整行func的返回值类型
func(Iter iter)
{
    ///
    return *iter;
}


int main(void)
{
    MyIter<int> ite(new int(8));
    std::cout <<func(ite) <<std::endl;
    return 0;
}
