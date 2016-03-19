#include <iostream>


class Singleton
{
public :
    static Singleton* GetInstancePoint( )           // 获取对象单例的指针
    {
        return const_cast<Singleton *>(Singleton::m_singleton);
    }

    static void DestroyInstance( )                  // 销毁单例对象的空间
    {
        if(Singleton::m_singleton != NULL)
        {
            delete Singleton::m_singleton;
            Singleton::m_singleton = NULL;
        }
    }
private :
    Singleton( )                                // 构造函数[被保护]
    {
    }

    Singleton(const Singleton &singleton)       // 赋值构造函数[被保护]
    {

    }

    ~Singleton( )                               // 析构函数
    {

    }

    static Singleton *m_singleton;                // 指向单例对象的指针
};




///////////
Singleton* Singleton::m_singleton = new Singleton( );                // 指向单例对象的指针
///////////


int main()
{
    Singleton *sp1 = Singleton::GetInstancePoint( );
    Singleton *sp2 = Singleton::GetInstancePoint( );

    std::cout <<(sp1 == sp2) <<std::endl;

    Singleton::DestroyInstance( );

    return 0;
}
