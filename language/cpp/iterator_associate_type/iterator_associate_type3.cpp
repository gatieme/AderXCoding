///c++11 条款1：理解模板类型推导
///http://blog.csdn.net/coolmeme/article/details/43986163
///http://blog.csdn.net/shinehoo/article/details/5722362
///  STL源码剖析 PDF-119/534

#include <iostream>
#include <typeinfo>


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


///// 泛化的C接收任意类型
//template <typename T>
//class C             //  这个泛化版本允许接受T为任意类型
//{
//    // NOP...
//};
//
//
///// 特化的类C接收原生的指针作为对象
//template <typename T>
//class C<T*>             //  这个泛化版本适用于"T为原生指针的情况"
//{
//    //  T为原生指针便是T为任何型别的一个更进一步的条件限制
//    // NOP...
//};


//  泛化的iterator_traits对象
template <typename Iter>
struct iterator_traits
{
    typedef typename Iter::value_type value_type;
};

// 特化的iterator_traits接收<T*>参数, 萃取出一个T类型
template<class T>
struct iterator_traits<T *>
{
    typedef T value_type;
};

// 特化的iterator_traits接收<const T*>参数, 萃取出一个T型
template<class T>
struct iterator_traits<const T *>
{
    typedef T value_type;
};


template <class Iter>
//typename Iter::value_type          ///  这一整行func的返回值类型
typename iterator_traits<Iter>::value_type
func(Iter iter)
{
    ///
    return *iter;
}



int main(void)
{

    MyIter<int> ite(new int(8));
    std::cout <<func(ite) <<std::endl;


    std::cout <<typeid(iterator_traits< MyIter<int> >::value_type).name();
    std::cout <<typeid(iterator_traits<int *>::value_type).name();
    std::cout <<typeid(iterator_traits<const int *>::value_type).name();


    return 0;
}
