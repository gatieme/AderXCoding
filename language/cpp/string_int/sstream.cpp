#include <iostream>
#include <string>
#include <sstream>

using namespace std;
template<typename T>
string ToString(const T& t)
{

    ostringstream oss;//创建一个流

    oss <<t;//把值传递如流中
    return oss.str();//获取转换后的字符转并将其写入result
}

template<>
const char* Convert<const char *, string>(const string &str)
{
    return str.c_str( );
}

template<typename out_type, typename in_value>
out_type Convert(const in_value & t)
{

    stringstream stream;

    stream <<t;          //向流中传值
    out_type result;    //这里存储转换结果
    stream >>result; //向result中写入值

    return result;
}





int main()
{
    cout <<ToString(12.345) <<endl;
    cout <<ToString(12) <<endl;

    cout <<Convert<double>("12.345") <<endl;
    cout <<Convert<int>("12.345") <<endl;
    cout <<Convert<float>("12.345") <<endl;
    cout <<Convert<const char *>("12.345") <<endl;


    return 0;
}
