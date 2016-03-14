#include <iostream>  
  
// 目标类 -=> 对应于目标抽象类，内含我们现在项目需要的接口  
// 相当于20V的电压接口  
class Target  
{  
public :  
    virtual ~Target( )  
    {  
  
    }  
  
    virtual void Request( )            // 希望获得的系统接口  
    {  
        std::cout <<"Target::Request" <<std::endl;  
    }  
};  
  
  
// 需要适配的类, 内含不符合要求的接口  
// 相当于已经提供好的220V的电压插座接口  
class Adaptee  
{  
public :  
    void SpecialRequest( )  
    {  
        std::cout <<"Adaptee::SpecialRequest..." <<std::endl;  
    }  
};  
  
  
// 获取接口的适配器类,  
// 适配后的符合要求的接口  
// 将目标类Adatee中不符合要求的接口， 转换为Target中的接口类型  
// 相当于一个转接器，将成员m_adaptee[Adaptee]的220V电压接口, 转换成Target类的20V电压接口  
class Adapter : public Target  
{  
public :  
    Adapter( )  
    :m_adaptee(new Adaptee)  
    {  
        //this->m_adaptee = new Adaptee( );  
    }  
  
    ~Adapter( )  
    {  
        if(this->m_adaptee != NULL)  
        {  
            delete this->m_adaptee;  
            this->m_adaptee = NULL;  
        }  
    }  
  
  
    void Request( )         // 我们需要的目标接口  
    {  
        // 将成员m_adaptee[Adaptee]的220V电压接口, 转换成Target类的20V电压接口  
        this->m_adaptee->SpecialRequest( ); // 调用适配类的特殊(不符合)接口  
    }  
  
    Adaptee *m_adaptee;  
};  
  
  
int main(void)  
{  
    Target *target = new Adapter( );            // 定义一个目标接口  
    target->Request( );  
  
  
    delete target;  
    target = NULL;  
  
}  