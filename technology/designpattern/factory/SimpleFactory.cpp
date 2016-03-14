#include <iostream>  
  
// 生成产品依据标识   
typedef enum ClassType  
{  
    SINGCORE_A,  
    SINGCORE_B,   
}ClassType;  
  
  
////////////////////////////////////////////////////////////////////////////////  
// 基础产品类 -=> 对应于抽象产品角色  
class SingCore  
{  
public :  
    virtual ~SingCore( ){ };        // 虚析构函数   
      
    virtual void Show( ) = 0;       // 产品的显示函数   
};  
  
// 单核产品S -=> 对应于具体产品角色  
class SingCoreA : public SingCore  
{  
public :  
    virtual ~SingCoreA( ){ };       // 虚析构函数   
      
    void Show( )  
    {  
        std::cout <<"SingCore A..." <<std::endl;   
    }   
};    
  
  
// 单核产品B -=> 对应于具体产品角色  
class SingCoreB : public SingCore  
{  
public :  
    virtual ~SingCoreB( ){ };       // 虚析构函数   
      
    void Show( )  
    {  
        std::cout <<"SingCore B..." <<std::endl;   
    }     
};   
////////////////////////////////////////////////////////////////////////////////  
//  
//  
//  
////////////////////////////////////////////////////////////////////////////////  
// 工厂类 -=> 对应于工厂角色  
class Factory  
{  
public :  
    virtual ~Factory( ){ };             // 虚析构函数   
  
    SingCore* CreateSingCore(ClassType classType)  
    {   
        switch(classType)  
        {  
            case SINGCORE_A :  
            {  
                return new SingCoreA( );   
            }  
              
            case SINGCORE_B :  
            {  
                return new SingCoreB( );  
            }  
        }  
    }   
};  
////////////////////////////////////////////////////////////////////////////////  
//  
//  
//  
////////////////////////////////////////////////////////////////////////////////  
  
  
int main()  
{  
      
    Factory *factory = new Factory( );  
      
    factory->CreateSingCore(SINGCORE_A)->Show( );   
    factory->CreateSingCore(SINGCORE_B)->Show( );  
          
    delete factory;   
}  