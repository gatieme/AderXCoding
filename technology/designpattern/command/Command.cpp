// 命令的接受者，是真正执行命令的对象  
class Receiver  
{  
public :  
    virtual void Action()  
    {  
        std::cout <<"do something..." <<endl;  
    }  
};  


// 命令的接口  
class Command  
{  
public :  
    virtual void Execute( ) = 0;        // 定义了一个执行的方法  
};  
  
// 命令接口的实现对象，执行一个命令，  
// 通常会持有接收者，并调用接收者的功能来完成命令要执行的操作。  
class ConcreteCommand : public  Command  
{  
public :  
    ConcreteCommand(Receiver *receiver)  
    {  
       this->receiver = receiver;  
    }  
  
    void Execute()  
    {  
  
       //通常会转调接收者对象的相应方法，让接收者来真正执行功能  
       receiver->Action();  
  
    }  
protected:  
    Receiver *receiver; // 内含一个命令接收者  
};  


// 要求命令对象执行请求，  
// 通常会持有命令对象，可以持有很多的命令对象  
class Invoker  
{  
public :  
    void SetCommand(Command *command)  
    {  
       this->command = command;  
    }  
  
    void RunCommand()  
    {  
        command->Execute();  
    }  
protected:  
    Command *command;  
  
};  


int main( )  
{  
    //创建接收者  
    Receiver *receiver = new Receiver;  
  
    //创建命令对象，设定它的接收者  
    Command *command = new ConcreteCommand(receiver);  
  
    //创建Invoker，把命令对象设置进去  
  
    Invoker *invoker = new Invoker;  
    invoker->SetCommand(command);        // invoker发出command命令  
    invoker->RunCommand( );              // 然后去执行这个命令  
  
}  