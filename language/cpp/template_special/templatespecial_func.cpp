#include <iostream>
#include <cstring>

///  模版特化

template <class T>
int compare(const T left, const T right)
{
    std::cout <<"in template<class T>..." <<std::endl;
    return (left - right);
}


//  这个是一个特化的函数模版
template < >
int compare<const char*>(const char* left, const char* right)
{
    std::cout <<"in special template< >..." <<std::endl;

    return strcmp(left, right);
}
//  特化的函数模版, 两个特化的模版本质相同, 因此编译器会报错
// error: redefinition of 'int compare(T, T) [with T = const char*]'|
//template < >
//int compare(const char* left, const char* right)
//{
//    std::cout <<"in special template< >..." <<std::endl;
//
//    return strcmp(left, right);
//}


//  这个其实本质是函数重载
int compare(char* left, char* right)
{
    std::cout <<"in overload function..." <<std::endl;

    return strcmp(left, right);
}

int main( )
{
    compare(1, 4);

    const char *left = "gatieme";
    const char *right = "jeancheng";
    compare(left, right);

    return 0;
}
