#include <iostream>

//公共抽象类
// 对应于 -=> 抽象构件（Component）角色
class Pad
{
public:
    Pad(){ }
    virtual ~Pad(){ }
    virtual void Show( ) = 0;
};


// 具体构件（Concrete Component）角色
class IPad : public Pad
{
public :
    IPad( ){ }
    virtual ~IPad( ){  };

    void Show( )
    {
        std::cout <<"新的Ipad Mini..." <<std::endl;
    }
};


// 装饰（Decorator）角色：
class Decorator : public Pad

{
public :
    Decorator(Pad *pad)
    {
        m_pad = pad;
    }
    virtual ~Decorator( ){ };

    void Show( )
    {
        this->m_pad->Show( );       // 展示一下自己的手机
    }

protected:
    Pad *m_pad;

    virtual void AddDecorator( ) = 0;

};

// 具体装饰（Concrete Decorator）角色
class CoverDecorator : public Decorator
{
public :
    CoverDecorator(Pad *pad)
    :Decorator(pad)
    {
    }

    virtual ~CoverDecorator( ){ }

    void Show( )
    {
        this->AddDecorator( );
        Decorator::Show( );
    }

protected:
    void AddDecorator( )
    {
        std::cout <<"弄了个保护套";
    }

};

// 具体装饰（Concrete Decorator）角色
class FoilDecorator : public Decorator
{
public :
    FoilDecorator(Pad *pad)
    :Decorator(pad)
    {
    }
    virtual ~FoilDecorator( ){ }

    void Show( )
    {
        this->AddDecorator( );
        Decorator::Show( );
    }

protected:
    void AddDecorator( )
    {
        std::cout <<"贴了个的贴膜...";
    }

};


int main( )
{
    // 现在我买了一个IpadMini
    Pad *pad = new IPad( );
    pad->Show( );               // 跑出去得瑟一下

    // 不行，还需要加个保护套
    Pad *coveDeco = new CoverDecorator(pad);
    coveDeco->Show( );               // 现在可以了吧，再出去得色一下

    // 好吧，再来个贴膜
    Pad *foilDeco = new FoilDecorator(coveDeco);
    foilDeco->Show( );
}
