#include <iostream>


class Singleton
{
public :
    static Singleton* GetInstance( )           // 获取对象单例的指针
    {
        // 此处进行了两次m_Instance == NULL的判断，
        // 是借鉴了Java的单例模式实现时，
        // 使用的所谓的“双检锁”机制。
        // 因为进行一次加锁和解锁是需要付出对应的代价的，
        // 而进行两次判断，就可以避免多次加锁与解锁操作，
        // 同时也保证了线程安全
        if(Singleton::m_singleton == NULL)          //
        {
            Lock( );            // 此处可以调用其他库的锁线程，或者自己实现一个
            if(Singleton::m_singleton == NULL)       // 如果单例对象没有创建， 则将其创建
            {
                Singleton::m_singleton = new Singleton( );
            }
            Unlock( );      // 此处可以调用其他库的锁线程，或者自己实现一个
        }
        return Singleton::m_singleton;
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

int main()
{
    Singleton *sp1 = Singleton::GetInstance( );
    Singleton *sp2 = Singleton::GetInstance( );

    std::cout <<(sp1 == sp2) <<std::endl;

    Singleton::DestroyInstance( );

    return 0;
}
