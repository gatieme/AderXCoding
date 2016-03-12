#include <iostream>


#include <cstring>


class Base
{
public :
    explicit Base(const char *str)
    {
        std::cout <<"constructor..." <<std::endl;

        this->m_length = strlen(str);
        this->m_cstr = new char[this->m_length + 1];

        strcpy(this->m_cstr, str);
    }

    Base(const Base &base)
    {
        this->m_length = base.m_length;
        this->m_cstr = new char[this->m_length + 1];

        strcpy(this->m_cstr, base.m_cstr);
    }

    ~Base()
    {
        delete this->m_cstr;
    }

protected :

    char *m_cstr;
    int  m_length;
};



int main(void)
{
    Base base = (char *)10000;     // 隐含的类型转换操作符

    return 0;
}
