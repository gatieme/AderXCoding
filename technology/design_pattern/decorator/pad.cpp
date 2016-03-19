#include <iostream>
using namespace std;

// pad类的抽象接口
class Pad
{
public:
    Pad(){ }
    virtual ~Pad(){ }
    virtual void Show( ) = 0;
};

// 新的IPadMini
class IPad : public Pad
{
public :
    IPad( ){ }
    virtual ~IPad( ){  };

    void Show( )
    {
        std::cout <<"a new Ipad Mini..." <<endl;
    }
};

// 加了保护套的IPadMini
class CoverIPad : public IPad
{
public :
    CoverIPad( ){ }
    virtual ~CoverIPad( ){  };

    void Show( )
    {
        std::cout <<"a new Cover Ipad Mini with a protecting jacket..." <<endl;
    }
};


int main( )
{
    // 给媳妇买了一个IpadMini
    Pad *pad1 = new IPad( );
    pad1->Show( );               // 跑出去得瑟一下

    // 现在我买了一个IpadMini
    Pad *pad2 = new CoverIPad( );
    pad2->Show( );               // 跑出去得瑟一下


}
