#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using namespace std;
/*
电视机是请求的接收者，
    也只有它的内部有一堆指令集合可以执行各种命令，它才是命令的真正执行者
    因此它有Open打开电视, Close关闭电视，Change更换频道的接口
遥控器是请求的发送者，
    它内含命令的对象，
    负责将这个命令发送出去，因此需要有设置命令的接口，相当于人按下遥控器的按钮
    内含RunCommand运行命令的接口，它调用了命令接口的Execute执行函数

遥控器上的那些按钮，
    不同的按钮对应电视机的不同操作。
    抽象命令角色由一个命令接口来扮演，
    有三个具体的命令类实现了抽象命令接口，
    这三个具体命令类分别代表三种操作：
    打开电视机、关闭电视机和切换频道。

显然，电视机遥控器就是一个典型的命令模式应用实例。
*/




// 接收者对象， 电视才是真正命令的执行者
class Television
{
public :
    void Open( )       // 打开电视
    {
        std::cout <<"打开电视" <<std::endl;
    }

    void Close( )      // 关闭电视
    {
        std::cout <<"关闭电视" <<std::endl;
    }

    void Change( )     // 切换频道
    {
        std::cout <<"更换频道" <<std::endl;
    }
};


class Command
{
public :
    virtual void Execute( ) = 0;         // 执行的接口
};

// 打开电视的命令
class OpenCommand : public Command
{
public :
    OpenCommand(Television *tv)
    {
        m_tv = tv;
    }

    void Execute( )         // 执行的接口
    {
        //std::cout <<"打开电视" <<std::endl;
        m_tv->Open( );
    }
protected :
    Television *m_tv;
};

// 关闭电视的命令
class CloseCommand : public Command
{
public :
    CloseCommand(Television *tv)
    {
        m_tv = tv;
    }
    void Execute( )         // 执行的接口
    {
        //std::cout <<"关闭电视" <<std::endl;
        m_tv->Close( );
    }
protected :
    Television *m_tv;
};

// 更换频道的命令
class ChangeCommand : public Command
{
public :
    ChangeCommand(Television *tv)
    {
        m_tv = tv;
    }
    void Execute( )         // 执行的接口
    {
        //std::cout <<"更换频道" <<std::endl;
        m_tv->Change( );
    }
protected :
    Television *m_tv;
};

// Invoker请求发送者
// 要求命令对象执行请求，
// 通常会持有命令对象，可以持有很多的命令对象
class Control
{
public :
    void SetCommand(Command *command)
    {
       this->m_command = command;
    }

    void RunCommand( )
    {
        m_command->Execute();
    }

protected:
    Command *m_command;

};

// 主程序其实就相当于我们人
int main( )
{
    // 我们手里有一个遥控器
    Control *control = new Control;

    // 家里有一个大彩电
    Television *tv = new Television;

    /// 首先我们打开电视机
    // 创建一个打开的命令, 这个命令只操纵tv这个对象
    Command *openCommand = new OpenCommand(tv);
    control->SetCommand(openCommand);
    control->RunCommand( );
    delete openCommand;


    // 换了好久频道也没找到好看的, 郁闷的关掉电视机
    // 创建一个更换频道的命令，这个命令只操纵tv这个对象
    Command *changeCommand = new ChangeCommand(tv);
    control->SetCommand(changeCommand);
    control->RunCommand( );
    delete changeCommand;

    // 换了好久频道也没找到好看的, 郁闷的关掉电视机
    // 创建一个关闭的命令, 这个命令只操纵tv这个对象
    Command *closeCommand = new CloseCommand(tv);
    control->SetCommand(closeCommand);
    control->RunCommand( );
    delete closeCommand;

    delete tv;
    delete control;
    return 0;
}
