#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// 核心产品基类  -=> 对应于抽象产品角色
class SingCore
{
public :
    virtual ~SingCore( ){ };        // 虚析构函数

    virtual void Show( ) = 0;       // 产品显示函数
};


// 核心产品A  -=> 对应于具体产品角色
class SingCoreA : public SingCore
{
public :
    virtual ~SingCoreA( ){ };       // 虚析构函数

    void Show( )        // 产品显示函数
    {
        std::cout <<"SingCore A..." <<std::endl;
    }
};

// 核心产品B  -=> 对应于具体产品角色
class SingCoreB : public SingCore
{
public :
    virtual ~SingCoreB( ){ };       // 虚析构函数

    void Show( )            // 产品显示函数
    {
        std::cout <<"SingCore B..." <<std::endl;
    }
};
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
////////////////////////////////////////////////////////////////////////////////
// 工厂的基类 -=> 对应于抽象工厂角色
class Factory
{
public:
    virtual ~Factory( ){ };         // 虚析构函数

    virtual SingCore* CreateSingCore( ) = 0;    // 生产产品的生产线

};

// 生产核心A的工厂 -=> 对应于具体产品角色
class FactoryA : public Factory
{
public :
    virtual ~FactoryA( ){ };            // 虚析构函数

    SingCoreA* CreateSingCore( )
    {
        return new SingCoreA( );
    }
};


// 生产核心B的工厂 -=> 对应于具体产品角色
class FactoryB : public Factory
{
public :
    virtual ~FactoryB( ){ };            // 虚析构函数

    SingCoreB* CreateSingCore( )
    {
        return new SingCoreB( );
    }
};

int main( )
{
    Factory *factoryA = new FactoryA( );
    factoryA->CreateSingCore( )->Show( );

    Factory *factoryB = new FactoryB( );
    factoryB->CreateSingCore( )->Show( );

    return 0;
}
