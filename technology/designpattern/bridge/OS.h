#ifndef __OS_H_INCLUDED__  
#define __OS_H_INCLUDED__  
  
  
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
  
  
  
#endif // __OS_H_INCLUDED__  