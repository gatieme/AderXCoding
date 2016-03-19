#include <iostream>


class Singleton
{
public :
    static Singleton* GetInstance( )   // 获取对象单例的指针
    {
        if(Singleton::m_singleton == NULL)   // 如果单例对象没有创建， 则将其创建
        {
            Singleton::m_singleton = new Singleton( );
        }

        return Singleton::m_singleton;
    }

    static void DestroyInstance( )  // 销毁单例对象的空间
    {
        if(Singleton::m_singleton != NULL)
        {
            delete Singleton::m_singleton;
            Singleton::m_singleton = NULL;
        }
    }

private :
    Singleton( )// 构造函数[被保护]
    {
    }

    Singleton(const Singleton &singleton)   // 赋值构造函数[被保护]
    {
    }


    static Singleton *m_singleton;// 指向单例对象的指针
};

////////////////////
Singleton* Singleton::m_singleton = NULL;// 指向单例对象的指针
////////////////////



int main()
{
Singleton *sp1 = Singleton::GetInstance( );
Singleton *sp2 = Singleton::GetInstance( );

std::cout <<(sp1 == sp2) <<std::endl;   // 两个对象的地址是相同的

Singleton::DestroyInstance( );

return 0;
}
