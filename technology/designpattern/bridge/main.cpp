#include <iostream>  
  
#include "OS.h"  
#include "Computer.h"  
  
using namespace std;  
  
int main()  
{  
    OS       *os = NULL;  
    Computer *com = NULL;  
  
    os = new WindowsOS( );  
    com = new DellComputer( );  
    com->InstallOS(os);              // 在Dell笔记本上安装Windows操作系统  
    delete os;  
    os = NULL;  
    delete com;  
    com = NULL;  
  
    os = new LinuxOS( );  
    com = new AcerComputer( );  
    com->InstallOS(os);      // 在宏基电脑上安装Linux操作系统  
    delete os;  
    os = NULL;  
    delete com;  
    com = NULL;  
  
    os = new MacOS( );  
    com = new AppleComputer( );  
    com->InstallOS(os); // 在苹果机上安装MacOs  
    delete os;  
    os = NULL;  
    delete com;  
    com = NULL;  
  
    return 0;  
}  