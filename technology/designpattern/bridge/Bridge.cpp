#include <iostream>  
  
//////////////////////////////////////////////////////////////////////////////////  
// 操作系统  
class OS  
{  
public :  
    virtual ~OS( ){ };  
    virtual void InstallOSImage( ) const = 0;          // 安装操作系统  
  
};  
  
  
// WINDOWS操作系统  
class WindowsOS : public OS  
{  
public:  
    virtual ~WindowsOS( ){  };  
    void InstallOSImage( ) const  
    {  
        std::cout <<"安装WINDOWS操作系统" <<std::endl;  
    }  
};  
  
// LINUX操作系统  
class LinuxOS : public OS  
{  
public:  
    virtual ~LinuxOS( ){ };  
    void InstallOSImage( ) const  
    {  
        std::cout <<"安装LINUX操作系统" <<std::endl;  
    }  
};  
  
  
// MACOX操作系统  
class MacOS : public OS  
{  
public:  
    virtual ~MacOS( ){ };  
    void InstallOSImage( ) const  
    {  
        std::cout <<"安装MACOS操作系统" <<std::endl;  
    }  
};  
//////////////////////////////////////////////////////////////////////////////////  
//  
//  
//  
//////////////////////////////////////////////////////////////////////////////////  
// 计算机的基类  
class Computer  
{  
public :  
    Computer(OS *os)  
    :m_os(os)  
    {  
    }  
  
    virtual ~Computer( )  
    {  
    };  
    virtual void InstallOS( ) = 0;          // 在计算机上安装操作系统  
  
protected :  
    OS  *m_os;                  // 安装的操作系统  
};  
  
// 计算机的基类  
class DellComputer : public Computer  
{  
public :  
    DellComputer(OS *os)  
    :Computer(os)  
    {  
    }  
    virtual ~DellComputer( ){ };  
    void InstallOS( )          // 在计算机上安装操作系统  
    {  
        std::cout <<"This is a DELL computer..." <<std::endl;  
        this->m_os->InstallOSImage( );                      // 安装操作系统的镜像  
        std::cout <<std::endl;  
    }  
};  
  
  
  
// 计算机的基类  
class AcerComputer : public Computer  
{  
public :  
    AcerComputer(OS *os)  
    :Computer(os)  
    {  
    }  
    virtual ~AcerComputer( )  
    {  
  
    }  
    void InstallOS( )          // 在计算机上安装操作系统  
    {  
        std::cout <<"This is a ACER computer..." <<std::endl;  
        this->m_os->InstallOSImage( );                      // 安装操作系统的镜像  
        std::cout <<std::endl;  
    }  
  
};  
  
// 计算机的基类  
class AppleComputer : public Computer  
{  
public :  
    AppleComputer(OS *os)  
    :Computer(os)  
    {  
    }  
    virtual ~AppleComputer( ){ };  
    void InstallOS( )          // 在计算机上安装操作系统  
    {  
        std::cout <<"This is a APPLE computer..." <<std::endl;  
        this->m_os->InstallOSImage( );                      // 安装操作系统的镜像  
        std::cout <<std::endl;  
    }  
  
};  
//////////////////////////////////////////////////////////////////////////////////  
//  
//  
//  
//  
//////////////////////////////////////////////////////////////////////////////////  
int main()  
{  
    OS       *os = NULL;  
    Computer *com = NULL;  
  
    os = new WindowsOS( );  
    com = new DellComputer(os);  
    com->InstallOS( );// Dell上安装了Windows  
    delete os;  
    os = NULL;  
    delete com;  
    com = NULL;  
  
    os = new LinuxOS( );  
    com = new AcerComputer(os);  
    com->InstallOS( );// 宏基上装了个Linux  
    delete os;  
    os = NULL;  
    delete com;  
    com = NULL;  
  
    os = new MacOS( );  
    com = new AppleComputer(os);  // 苹果电脑上安装MACOS  
    com->InstallOS( );  
    delete os;  
    os = NULL;  
    delete com;  
    com = NULL;  
  
    return 0;  
}  