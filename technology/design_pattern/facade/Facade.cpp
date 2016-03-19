#include <iostream>

using namespace std;


// 词法分析
class Lexicaler
{
public :
    void Lexical( )
    {
        std::cout <<"正在对源文件进行词法分析" <<std::endl;
    }
};

// 语法分析
class Parser
{
public :
    void Parse( )
    {
        std::cout <<"正在对源文件进行语法分析" <<std::endl;
    }
};

// 语义分析
class Semantier
{
public :
    void Semantic( )
    {
        std::cout <<"正在对源文件进行语义分析" <<std::endl;
    }
};


// 生成中间代码
class Gener
{
public :
    void Gen( )
    {
        std::cout <<"正在生成目标代码" <<std::endl;
    }
};


// 生成中间代码
class Asmer
{
public :
    void Asm( )
    {
        std::cout <<"正在生成目标代码" <<std::endl;
    }
};

// 连接
class Linker
{
public :
    void Link( )
    {
        std::cout <<"正在生成链接" <<std::endl;
    }
};


class Complier
{
public :
    void Comple( )
    {
        Lexicaler lexicaler;
        Parser parser;
        Semantier semantier;
        Gener   gener;
        Asmer   asmer;
        Linker  linker;

        lexicaler.Lexical( );
        parser.Parse( );
        semantier.Semantic( );
        gener.Gen( );
        asmer.Asm( );
        linker.Link( );
    }
};


int main(void)
{
    // 这是不用外观模式的代码
    // 但是其实我们并不关心编译的过程，
    // 我们需要的只是编译的结果，
    // 那个可执行程序才是我们想要的
    Lexicaler lexicaler;
    Parser parser;
    Semantier semantier;
    Gener   gener;
    Asmer   asmer;
    Linker  linker;

    lexicaler.Lexical( );
    parser.Parse( );
    semantier.Semantic( );
    gener.Gen( );
    asmer.Asm( );
    linker.Link( );

    // 使用外观模式
    Complier complier;
    complier.Comple( );
}