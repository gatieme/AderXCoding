#ifndef __COMPUTER_H_INCLUDED__  
#define __COMPUTER_H_INCLUDED__  
  
#include "OS.h"  
  
// 计算机的基类  
class Computer  
{  
public :  
    virtual ~Computer( ){ };  
    virtual void InstallOS(const OS *os) = 0;          // 在计算机上安装操作系统  
  
};  
  
// 计算机的基类  
class DellComputer : public Computer  
{  
public :  
    virtual ~DellComputer( ){ };  
    void InstallOS(const OS *os)          // 在计算机上安装操作系统  
    {  
        std::cout <<"我有台戴尔电脑..." <<std::endl;  
        os->InstallOSImage( );                      // 安装操作系统的镜像  
        std::cout <<std::endl;  
    }  
};  
  
  
  
// 计算机的基类  
class AcerComputer : public Computer  
{  
public :  
    virtual ~AcerComputer( ){ };  
    void InstallOS(const OS *os)          // 在计算机上安装操作系统  
    {  
        std::cout <<"我有台宏基电脑..." <<std::endl;  
        os->InstallOSImage( );                      // 安装操作系统的镜像  
        std::cout <<std::endl;  
    }  
  
};  
  
// 计算机的基类  
class AppleComputer : public Computer  
{  
public :  
    virtual ~AppleComputer( ){ };  
    void InstallOS(const OS *os)          // 在计算机上安装操作系统  
    {  
        std::cout <<"我有台苹果电脑..." <<std::endl;  
        os->InstallOSImage( );                      // 安装操作系统的镜像  
        std::cout <<std::endl;  
    }  
  
};  
#endif // __COMPUTER_H_INCLUDED__  