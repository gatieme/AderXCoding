C语言调用C++的函数库
=======

http://blog.csdn.net/coolmeme/article/details/7184331

http://www.educity.cn/develop/478645.html

http://blog.163.com/hbu_lijian/blog/static/1261291532012102571310685/


http://blog.csdn.net/caspiansea/article/details/9676153


#1	C++中调用C的接口
-------

我们在阅读一些库的代码的时候, 经常看到有些函数被extern "C"来修饰


##1.1	extern "C"引入C的库代码
-------


如下所示

```cpp
extern "C" void func();
```


如果需要修饰的函数比较多, 则使用如下方式



```cpp
#ifdef __cplusplus
extern "C"
{
#endif

/////////////////////
//  一段代码
/////////////////////

#ifdef __cplusplus
}
#endif
```

>如果你不想理解这段代码的意义, 那么请你记住 : 在你的代码不知道是被`c`调用还是`c++`调用时, 请添加此段代码.

下面详细说明此段代码的意义：
`__cplusplus`是`c++`编译器(如`g++`等)定义的宏, 如果是`c++`调用的话， `extern "C"`声明会有效. 如果时c调用的话, 那么, extern "C"`声明无效

要明白为何使用extern "C", 还得从cpp中对函数的重载处理开始说起.

在c++中，为了支持重载机制，在编译生成的汇编码中，要对函数的名字进行一些处理, 加入比如函数的返回类型等等. 而在C中, 只是简单的函数名字而已, 不会加入其他的信息.

也就是说 : `C++`和`C`在编译后对产生的函数名字的处理是不一样的. 而上面的代码`extern "C"`目的就是主要实现C与C++的相互调用问题.


对于C++编译器, 由于`__cplusplus`宏被定义`, 因此通过extern "C"`来通知C++编译器编译后的代码是按照C的obj文件格式编译的，要连接的话按照C的命名规则去找.


>`C`和`C++`对函数的处理方式是不同的. `extern "C"`是使`C++`能够调用`C`写作的库文件的一个手段, 如果要对编译器提示使用`C`的方式来处理函数的话, 那么就要使用`extern "C"`来说明.


这种方法有两种妙用

1.	在C源代码中使用extern "C"这样代码及时添加到C++的项目工程中, 也可以正常的被编译和链接

2.	多数情况下我们C的库都是SDK(包括头文件和lib包), 没有源代码, 那么在我们的C++代码中使用extern "C"就通知编译器我们引入了C库的代码


##1.2	示例程序
-------


我们在`add.c`中定义了一个add函数, 这个函数是C语言实现的函数接口

```cpp
// add.c
#include <stdio.h>
#include <stdlib.h>


int add(const int a, const int b)
{
    return (a + b);
}
```


我们C++中在main函数调用C语言实现的add函数

```cpp
//  main.cpp
#include <iostream>
using namespace std;



#ifdef __cplusplus
extern "C"
{
#endif

int add(const int a, const int b);

#ifdef __cplusplus
}
#endif



int main( )
{
    std::cout <<add(3, 4) <<std::endl;

    return 0;
}
```


下面是我们的`Makefile`信息, 我们生成了两个可执行程序main_normal和main_sdk

*	main_normal为main.o和add.o直接编译生成, C++中通过extern "C"直接以源码的方式生成了main_normal

*	main_sdk类似于我们开发的方式, 首先用add.c生成了一个sdk库libadd.so, 然后main.c中通过extern "C"以C的方式链接了libadd.so中的add函数, 生成了main_sdk

```cpp
#  the compile options
CFLAGS = -Wall -std=gnu99 -O2 -pedantic -Wextra -g
CXXFLAGS = -Wall -std=c++11 -O2 -pedantic -Wextra -g

SHAREDLIB_LINK_OPTIONS = -shared


FPIC = -fPIC

#  the include directory
INC = -I./


target=main_sdk main_normal libadd.so



all:$(target)



main_sdk : main.o libadd.so
	$(CXX) $^ -o $@ -L./ -ladd


main_normal : main.o add.o
	$(CXX) $^ -O $@

libadd.so : add.o
	$(CC) $(SHAREDLIB_LINK_OPTIONS) $(FPIC) $(LDFLAGS) $^ -o $@

#libmyclass.a:myclass.o func.o
#	ar crv $@ $^


%.o : %.cpp
	$(CXX) $(FPIC) $(CXXFLAGS) -c $^ -o $@ $(INC)


%.o : %.c
	$(CC) $(FPIC) $(CFLAGS) -c $^ -o $@ $(INC)


clean :
	rm -rf *.o
	rm -rf $(target)

```

![C++中调用C的函数](./cpp_link_c/cpp_link_c.png)




由于`C++`是高度兼容`C`的, 只需要通知C++编译器按照C的命名方式编译和链接二进制代码即可, 除了编译命名的处理不需要额外的层次, 因此这种方式很好的解决了, `C++`代码中编译链接`C`源代码的问题

但是`C`语言却不支持`C++`面向对象的特性, 这个问题该怎么解决啊.





**C调用C++的函数借口信息**


前面我们讲解了, C++是一个C基础上扩展的支持面向对象的高级语言, 因此我们将C调用C++的函数的方法分为面向过程和面向对象两种特性分开讨论.


*	C中调用C++中基本的数据和成员(面向过程的数据)

*	C中调用C++中类成员数据(面向对象的数据)








#2	C中调用C++中基本的数据和成员(面向过程的数据)
-------



C++面向过程的部分是完全兼容C的, 因此其本质上俊只是编译阶段的处理不同而已, 但是C++也引入了一些新的特性, 比如函数重载等, 这些需要我们单独去兼容.


##2.1	基本函数的处理
-------

这部分C与C++是完全兼容的, 没有区别, 因此使用extern "C"的方式就足以处理.

将C++函数声明为"extern "C"(在你的C++代码里做这个声明), 然后调用它(在你的C或者C++代码里调用). 例如：



```cpp
// C++ code:

extern "C" void f(int);

void f(int i)
{
	// ...
}

然后，你可以这样使用f()

```cpp
/* C code */
void f(int);
void cc(int i)
{
	f(i);
　　/* ... */
}
```





##2.2	重载函数的处理
-------


##2.2	C中调用C++中类成员数据(面向对象的数据)
-------


