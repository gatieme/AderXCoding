>本文更新记录  作者gatieme, [CSDN](http://blog.csdn.net/gatieme). [GitHub](https://github.com/gatieme)
>
> 2016-08-08 11:37, 添加了Linux内核内存检测工具[Kmemleak](http://blog.csdn.net/gatieme/article/details/51959654#t11)
>
>2016-08-08 11:43, 添加了链接[内存泄露检测工具比较 ](http://blog.163.com/zhuang_qianxin/blog/static/29765138201051092529107/)


Linux下编写C或者C++程序，有很多工具，但是主要编译器仍然是gcc和g++。最近用到STL中的List编程，为了检测写的代码是否会发现内存泄漏，了解了一下相关的知识。

所有使用动态内存分配(dynamic memory allocation)的程序都有机会遇上内存泄露(memory leakage)问题，在Linux里有三种常用工具来检测内存泄露的情況，包括：

参见 http://elinux.org/Memory_Debuggers

| 工具 | 描述 |
|:-------:|:-------:|
| [valgrind](http://elinux.org/Memory_Debuggers#valgrind) | 一个强大开源的程序检测工具 |
| [mtrace](http://elinux.org/Memory_Debuggers#mtrace) |GNU扩展, 用来跟踪malloc, mtrace为内存分配函数（malloc, realloc, memalign, free）安装hook函数 |
| [dmalloc]() | 用于检查C/C++内存泄露(leak)的工具，即检查是否存在直到程序运行结束还没有释放的内存,以一个运行库的方式发布 |
| memwatch | 和dmalloc一样，它能检测未释放的内存、同一段内存被释放多次、位址存取错误及不当使用未分配之内存区域
| [mpatrol](http://mpatrol.sourceforge.net/) | [一个跨平台的 C++ 内存泄漏检测器](http://www.ibm.com/developerworks/cn/linux/l-mleak2/) |  
| [dbgmem](http://dbgmem.sourceforge.net/) | 
| [Electric Fence](http://elinux.org/Electric_Fence) | 


#1	被测程序
-------

为了方便测试,,我们编写了一个简单的程序, 循环10次每次申请了一个100个字节的单元, 但是却不释放



#2	valgrind
-------

##2.1	valgrind介绍
-------

是不是说没有一种内存检查工具能够在Linux使用呢，也不是，像开源的valgrind工具还是相当不错的

*	Memcheck。这是valgrind应用最广泛的工具，一个重量级的内存检查器，能够发现开发中绝大多数内存错误使用情况，比如：使用未初始化的内存，使用已经释放了的内存，内存访问越界等。这也是本文将重点介绍的部分。

*	Callgrind。它主要用来检查程序中函数调用过程中出现的问题。

*	Cachegrind。它主要用来检查程序中缓存使用出现的问题。

*	Helgrind。它主要用来检查多线程程序中出现的竞争问题。

*	Massif。它主要用来检查程序中堆栈使用中出现的问题。

*	Extension。可以利用core提供的功能，自己编写特定的内存调试工具

| 主页 | 下载 |
|:-------:|:-------:|
| [valgrind](http://valgrind.org/) |  [downloads](http://valgrind.org/downloads/current.html#current) |

![valgrind介绍](http://img.blog.csdn.net/20160719211251895)

>参照
>
>[Valgrind简单用法](http://www.cnblogs.com/sunyubo/archive/2010/05/05/2282170.html)
>
>[Unix下C程序内存泄漏检测工具Valgrind安装与使用](http://blog.csdn.net/sduliulun/article/details/7732906)
>
>[valgrind 的使用简介](http://blog.csdn.net/sduliulun/article/details/7732906)
>
>[应用 Valgrind 发现 Linux 程序的内存问题](http://www.ibm.com/developerworks/cn/linux/l-cn-valgrind/)
>
>[如何使用Valgrind memcheck工具进行C/C++的内存泄漏检测](http://www.oschina.net/translate/valgrind-memcheck)


##2.2	安装
-------

**源码安装**



到[下载地址](http://valgrind.org/downloads/current.html#current))下载最新版的valgrind,按照里面的README提示，安装后就可以使用这个工具来检测内存泄露和内存越界等

```c
/configure

make

sudo make install
```



当然也可以使用发行版的自带的源中安装

```c
sudo apt install valgrind
```

这是一个没有界面的内存检测工具，安装后，输入 valgrind ls -l 验证一下该工具是否工作正常（这是README里面的方法，实际上是验证一下对ls -l命令的内存检测），如果你看到一堆的信息说明你的工具可以使用了。



 

##2.3	使用说明
-------


Valgrind工具包包含多个工具，如Memcheck,Cachegrind,Helgrind, Callgrind，Massif。

**Memcheck**

最常用的工具，用来检测程序中出现的内存问题，所有对内存的读写都会被检测到，一切对malloc()/free()/new/delete的调用都会被捕获。所以，Memcheck 工具主要检查下面的程序错误

| 内容 | 描述 |
|:------:|:-------:|
| 使用未初始化的内存 | Use of uninitialised memory |
| 使用已经释放了的内存 | Reading/writing memory after it has been free’d |
| 使用超过 malloc分配的内存空间 | Reading/writing off the end of malloc’d blocks |
| 对堆栈的非法访问 | Reading/writing inappropriate areas on the stack |
| 申请的空间是否有释放 | Memory leaks – where pointers to malloc’d blocks are lost forever |
| malloc/free/new/delete申请和释放内存的匹配 | Mismatched use of malloc/new/new [] vs free/delete/delete [] |
| src和dst的重叠 | Overlapping src and dst pointers in memcpy() and related functions | 

这些问题往往是C/C++程序员最头疼的问题，Memcheck在这里帮上了大忙。 

**Callgrind**

和gprof类似的分析工具，但它对程序的运行观察更是入微，能给我们提供更多的信息。和gprof不同，它不需要在编译源代码时附加特殊选项，但加上调试选项是推荐的。Callgrind收集程序运行时的一些数据，建立函数调用关系图，还可以有选择地进行cache模拟。在运行结束时，它会把分析数据写入一个文件。callgrind_annotate可以把这个文件的内容转化成可读的形式。 

**Cachegrind**

Cache分析器，它模拟CPU中的一级缓存I1，Dl和二级缓存，能够精确地指出程序中cache的丢失和命中。如果需要，它还能够为我们提供cache丢失次数，内存引用次数，以及每行代码，每个函数，每个模块，整个程序产生的指令数。这对优化程序有很大的帮助。 

**Helgrind**

它主要用来检查多线程程序中出现的竞争问题。Helgrind寻找内存中被多个线程访问，而又没有一贯加锁的区域，这些区域往往是线程之间失去同步的地方，而且会导致难以发掘的错误。Helgrind实现了名为“Eraser”的竞争检测算法，并做了进一步改进，减少了报告错误的次数。不过，Helgrind仍然处于实验阶段。 

**Massif**

堆栈分析器，它能测量程序在堆栈中使用了多少内存，告诉我们堆块，堆管理块和栈的大小。Massif能帮助我们减少内存的使用，在带有虚拟内存的现代系统中，它还能够加速我们程序的运行，减少程序停留在交换区中的几率。 

>此外，lackey和nulgrind也会提供。Lackey是小型工具，很少用到；Nulgrind只是为开发者展示如何创建一个工具





>**注意**
>
>Valgrind不检查静态分配数组的使用情况
>
>Valgrind占用了更多的内存--可达两倍于你程序的正常使用量
>
>如果你用Valgrind来检测使用大量内存的程序就会遇到问题，它可能会用很长的时间来运行测试





##2.4	使用说明
-------

编译程序

```c
g++ -g -o leak leak.c 
```

被检测程序加入 –g   -fno-inline 编译选项保留调试信息, 否则后面的valgrind不能显示到出错行号。


valgrind被设计成非侵入式的，它直接工作于可执行文件上，因此在检查前不需要重新编译、连接和修改你的程序。要检查一个程序很简单，只需要执行下面的命令就可以了。

```c
valgrind --tool=tool_name program_name
```


比如我们要对ls -l命令做内存检查，只需要执行下面的命令就可以了



```c
valgrind --tool=memcheck ls -l
```

>小提示
>如果不知道有哪些参数, 可以先输入valgrind --tool=, 然后狂按两次tab, 会输出linux系统的只能提示, 同样,如果你输入了valgrind --tool=mem再狂按两次tab,linux系统会为你自动补全


##2.5	使用valgrind检测Memcheck
-------

 

下面我们就可以用valgrind对我们的程序检测leak



```c
valgrind --tool=memcheck --leak-check=full --show-reachable=yes --trace-children=yes    ./leak
```



其中--leak-check=full 指的是完全检查内存泄漏，

--show-reachable=yes是显示内存泄漏的地点，

--trace-children=yes是跟入子进程。



当程序正常退出的时候valgrind自然会输出内存泄漏的信息原理：

![输出内存泄漏的信息原](http://img.blog.csdn.net/20160719210756831)


#3	mtrace检测内存泄露
-------


##3.1	mtrace简介
-------

在一般的linux发行版中，有一个自带的工具可以很方便的替你完成这些事，这个工具就是mtrace. 

mtrace其实是GNU扩展函数，用来跟踪malloc。

mtrace为内存分配函数（malloc, realloc, memalign, free）安装hook函数。这些hook函数记录内存的申请和释放的trace信息。
在程序中，这些trace信息可以被用来发现内存泄漏和释放不是申请的内存。
当调用mtrace，mtrace会检查环境变量MALLOC_TRACE。该环境变量应该包含记录trace信息的文件路径。如果文件可以被成功打开，它的大小被截断为0。
如果MALLOC_TRACE没有设置，或者设置的文件不可用或者不可写，那么将不会安装hook函数，mtrace不生效。

详细说明可参考man page：man 3 mtrace

##3.2	mtrace使用
-------

mtrace能监测程序是否内存泄露

*	在程序的起始处包含头文件<mcheck.h>
```c
#include <mcheck.h>
```
*	更改环境变量：export   MALLOC_TRACE="mtrace.out"可以加入如下代码
```c
setenv("MALLOC_TRACE", "mtrace.out", 1);
```

*	调用函数mtrace()

```c
mtrace()
```

*	编译程序带上 -g 选项
```c
gcc -g -c leak_mtrace.c -o leak_mtrace.o  -std=gnu9x -Wall
```
 

*	运行程序一次，尽量调用所有程序内的函数。这时调试信息就已经被写入我们指定的mtrace.out文件中
```c
./leak_mtrace 
```



*	mtrace a.out  mtrace.out查看内存监测情况
```c
mtrace a.out  mtrace.out
```

![这里写图片描述](http://img.blog.csdn.net/20160719214131721)


#4	dmalloc
-------
 
dmalloc是一种用于检查C/C++内存泄露(leak)的工具，即检查是否存在直到程序运行结束还没有释放的内存，并且能够精确指出在哪个源文件的第几行。



#5	Linux内核的Kmemleak


##5.1	Kmemleak检测工具介绍
-------


Kmemleak工作于内核态是内核自带的内核泄露检测工具, 其源代码位于[mm/kmemleak.c](http://lxr.free-electrons.com/source/mm/kmemleak.c?v4.7)

Kmemleak工作于内核态，Kmemleak 提供了一种可选的内核泄漏检测，其方法类似于跟踪内存收集器。当独立的对象没有被释放时，其报告记录在 /sys/kernel/debug/kmemleak中，Kmemcheck能够帮助定位大多数内存错误的上下文。

##5.2	Kmemleak使用过程概述


*	首先`CONFIG_DEBUG_KMEMLEAK在Kernel hacking中被使能.

*	查看内核打印信息详细过程如下：

	1.	挂载debugfs文件系统
   mount -t debugfs nodev /sys/kernel/debug/
	2.	开启内核自动检测线程
   echo scan > /sys/kernel/debug/kmemleak
	3.	查看打印信息
   cat /sys/kernel/debug/kmemleak
	4.	清除内核检测报告，新的内存泄露报告将重新写入/sys/kernel/debug/kmemleak
   echo clear > /sys/kernel/debug/kmemleak

内存扫描参数可以进行修改通过向/sys/kernel/debug/kmemleak 文件写入。 参数使用如下

```cpp
off 禁用kmemleak（不可逆）
stack=on 启用任务堆栈扫描(default)
stack=off 禁用任务堆栈扫描
scan=on 启动自动记忆扫描线程(default)
scan=off 停止自动记忆扫描线程
scan=<secs> 设置n秒内自动记忆扫描
scan 开启内核扫描
clear 清除内存泄露报告
dump=<addr> 转存信息对象在<addr>
```

通过“kmemleak = OFF”，也可以在启动时禁用Kmemleak在内核命令行。在初始化kmemleak之前，内存的分配或释放这些动作被存储在一个前期日志缓冲区。这个缓冲区的大小通过配CONFIG_DEBUG_KMEMLEAK_EARLY_LOG_SIZE设置。 

##5.3	Kmemleak动态检测原理
-------


通过的kmalloc、vmalloc、kmem_cache_alloc等内存分配会跟踪其指针，连同其他的分配大小和堆栈跟踪信息，存储在PRIO搜索树。相应的释放函数调用跟踪和指针就会从kmemleak数据结构中移除。
分配的内存块，被认为是独立的，如果没有指针指向它起始地址或块的内部的任何位置，可以发现扫描内存（包括已保存的寄存器）。这意味着，有可能没有办法为内核通过所分配的地址传递块到一个释放函数，因此，该块被认为是一个内存泄漏。

扫描算法步骤：
1.	标记的所有分配对象为白色（稍后将剩余的白色物体考虑独立的）

2.	扫描存储器与所述数据片段和栈开始，检查对地址的值存储在PRIO搜索树。如果一个白色的对象的指针被发现，该对象将被添加到灰名单

3.	扫描的灰色对象匹配的地址（一些白色物体可以变成灰色，并添加结束时的灰名单），直到黑色集结束

4.	剩下的白色物体被认为是独立儿，并报告写入/sys/kernel/debug/kmemleak。
一些分配的内存块的指针在内核的内部数据结构和它们不能被检测为孤儿。对避免这种情况，kmemleak也可以存储的数量的值，指向一个内的块的地址范围内的地址，需要找到使块不被认为是泄漏.


##5.4	kmem相关函数
-------


从kernel源代码中的目录`include /linux/kmemleak.h`中可查看函数原型的头

|   函数  |   功能   |
|:-------:|:-------:|
| kmemleak_init | 初始化kmemleak |
| kmemleak_alloc | 一个内存块分配的通知 |
| kmemleak_alloc_percpu | 通知的一个percpu的内存块分配 |
| kmemleak_free | 通知的内存块释放 |
| kmemleak_free_part | 通知释放部分内存块 |
| kmemleak_free_percpu | 一个percpu内存块释放的通知 |
| kmemleak_not_leak | 当不是泄露时，标记对象 |
| kmemleak_ignore | 当泄漏时不扫描或报告对象 |
| kmemleak_scan_area | 添加扫描区域内的内存块 |
| kmemleak_no_scan | 不扫描的内存块 |
| kmemleak_erase | 删除一个指针变量的旧值 |
| kmemleak_alloc_recursive | 为kmemleak_alloc，只检查递归 |
| kmemleak_free_recursive | 为kmemleak_free，只检查递归 |