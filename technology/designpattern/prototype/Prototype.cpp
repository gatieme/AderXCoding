#include <iostream>  
#include <cstring>  
  
  
  
/// 原型抽象类 -=> 对应于抽象原型（Prototype）角色  
class Prototype  
{  
public :  
    Prototype( ){  };  
  
    virtual ~Prototype( ){ };  
  
    virtual Prototype* Clone( ) const = 0;  // 拷贝函数，原型模式的精髓所在  
  
    virtual void Show( ) const = 0;                // 显示当前信息  
};  
  
  
  
  
  
/// 原型类A -=> 对应于具体原型（Concrete Prototype）角色：  
class PrototypeA : public Prototype  
{  
public :  
    PrototypeA(const char *name = NULL)           // 构造函数  
    {  
        if(name == NULL)  
        {  
            this->m_name = new char[1];  
            strcpy(this->m_name, "");  
        }  
        else  
        {  
            this->m_name = new char[strlen(name) + 1];  
            strcpy(this->m_name, name);  
        }  
    }  
  
    PrototypeA(const PrototypeA &Prototype)               // 实现深拷贝  
    {  
        this->m_name = new char[strlen(Prototype.m_name)];  
        strcpy(this->m_name, Prototype.m_name);  
    }  
  
    virtual ~PrototypeA( )                 // 虚析构函数  
    {  
        delete[] this->m_name;  
    }  
  
    Prototype* Clone( ) const  // 拷贝函数，原型模式的精髓所在  
    {  
        return new PrototypeA(*this);  
    }  
  
    void Show( ) const                // 显示当前函数信息  
    {  
    std::cout <<"PrototypeA's name is " <<this->m_name <<std::endl;  
    }  
protected :  
    char *m_name;  
};  
  
  
/// 原型类B -=> 对应于具体原型（Concrete Prototype）角色：  
class PrototypeB : public Prototype  
{  
public :  
    PrototypeB(int no)          // 构造函数  
    {  
        m_no = no;  
    }  
    PrototypeB(const PrototypeB &prototype)               //  
    {  
        this->m_no = prototype.m_no;  
    }  
  
    virtual ~PrototypeB( )                // 虚析构函数  
    {  
  
    }  
    Prototype* Clone( ) const  // 拷贝函数，原型模式的精髓所在  
    {  
        return new PrototypeB(*this);  
    }                      // 获取名字的函数  
    void Show( ) const                // 显示当前函数信息  
    {  
        std::cout <<"PrototypeB's no is " <<this->m_no <<std::endl;  
    }  
protected :  
    int     m_no;  
};  
  
  
  
  
int main()  
{  
    Prototype *r1 = new PrototypeA("A");  
    Prototype *r2 = r1->Clone( );  
  
    // r1和r2是相同内容的副本  
    r1->Show( );  
    r2->Show( );  
    delete r1;  
    delete r2;  
    r1 = r2 = NULL;  
  
    Prototype *r3 = new PrototypeB(10);  
    Prototype *r4 = r3->Clone( );  
    // r1和r2是用相同内容的拷贝  
    r3->Show( );  
    r4->Show( );  
    delete r3;  
    delete r4;  
    r3 = r4 = NULL;  
  
    return 0;  
}  