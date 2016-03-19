#include <iostream>  
  
// 目标接口信息  
class Target  
{  
public :  
    virtual void Request( )            // 希望获得的系统接口  
    {  
        std::cout <<"Target::Request" <<std::endl;  
    }  
};  
  
  
// 需要适配的类, 内喊不符合要求的接口  
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
class Adapter : public Target, Adaptee  
{  
public :  
    void Request( )  
    {  
        Adaptee::SpecialRequest( );  
    }  
};  
  
  
int main()  
{  
    Target *target = new Adapter( );  
    target->Request( );  
  
  
    delete target;  
    target = NULL;  
  
    return 0;  
}  