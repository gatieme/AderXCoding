几款优秀的Linux基准测试工具
=======
| CSDN | GitHub |
|:----:|:------:|
| [几款优秀的Linux基准测试工具](http://blog.csdn.net/gatieme) | [`AderXCoding/system/tools/benchmark`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/benchmark) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢.
<br>



#1	性能基准测试工具
-------


基准测试是指运行计算机程序去评估硬件和软件性能的行为. 硬件基本测试包括评估处理器, 内存, 显卡, 硬盘, 网络等不同组件的性能.

基准测试有两类 : **复合**和**应用**

*	**复合基准**对一个硬件执行压力测试, 如连续写入和读取数据. 应用基准则是衡量真实世界应用程序如数据库和服务器的性能.

*	**基准测试软件**可以让系统测试者和用户客观独立的评估硬件性能.


依据其测试类型的不同可以分为 基准性能测试, 文件 `I/O` 性能测试, 网络性能测试, 以及多功能的性能测试工具


`Linux`下有许多优秀的开源`Linux`基准测试工具, 如`Phoronix Test Suite`，`IOzone`，`netperf`等,



#2	标准的性能基准测试工具
-------


| benchmark | 描述 |
|:---------:|:---:|
| sysbench | `sysbench` 是一款开源的多线程性能测试工具, 可以执行 `CPU`/内存/线程/`IO`/数据库等方面的性能测试. 简介数据库目前支持 `MySQL/Oracle/PostgreSQL` |
| hackbench | 源码下载地址 [`hackbench.c`](http://people.redhat.com/mingo/cfs-scheduler/tools/hackbench.c), 改进的用于测试调度器性能的 benchmark 工具, 就一个源文件,编译后运行即可, [手册](http://man.cx/hackbench) |
| unixbench | 一个用于测试`unix`系统性能的工具，也是一个比较通用的`benchmark`, 此测试的目的是对类`Unix` 系统提供一个基本的性能指示, 参见[Linux性能测试工具-UnixBench--安装以及结果分析](http://blog.csdn.net/gatieme/article/details/50912910) |
| CineBench | 很有说服力的一套CPU和显卡测试系统
| GreekBench | Geekbench测试你的计算机的CPU处理器和内存性能 |
| LLCbench | (底层表征基准测试 `ow-Level Characterization Benchmarks`) 是一个基准测试工具，集成了 `MPBench, CacheBench, 和 BLASBench` 测试方法 |
| HardInfo | 一个Linux系统信息查看软件. 它可以显示有关的硬件, 软件, 并进行简单的性能基准测试 |
| GtkPerf | 是一种应用程序设计，测试基于GTK +的性能 |


参见

[六款优秀的 Linux 基准测试工具](http://www.oschina.net/news/28468/6-linux-benchmark-tools)




#3	文件 `I/O` 性能基准测试工具
-------


| benchmark | 描述 |
|:---------:|:---:|
| iozone | iozone 是一款 `Linux` 文件系统性能测试工具. 它可以测 `Reiser4, ext3, ext4` |
| iometer | `Iometer` 是一个工作在单系统和集群系统上用来衡量和描述 `I/O` 子系统的工具 |
| bonnie++ | `Bonnie++` 是一个用来测试 `UNIX` 文件系统性能的测试工具, 主要目的是为了找出系统的性能瓶颈, 其名字来源于作者喜爱的歌手 `Bonnie Raitt` |
| dbench | Dbench和Tbench是用来模拟工业标准的Netbench负载测试工具来评估文件服务器的测试工具 |

参见[bonnie++、dbench、iozone工具](http://blog.csdn.net/adaptiver/article/details/7013150)




#4	网络性能测试工具
-------


`Netperf` 是一种网络性能的测量工具, 主要针对基于 `TCP或UDP` 的传输

`Netperf` 是一种网络性能的测量工具, 主要针对基于 `TCP` 或 `UDP` 的传输.

`Netperf` 根据应用的不同, 可以进行不同模式的网络性能测试, 即**批量数据传输(`bulk data transfer`)模式**和**请求/应答(`request/reponse`)模式**

`Netperf` 测试结果所反映的是两个系统之间发送和接受数据的速度和效 率。

Netperf工具是基于C／S模式的。server端是netserver，用来侦听来自client端的连接，client 端是netperf，用来向server发起网络测试。在client与server之间，首先建立一个控制连接，传递有关测试配置的信息，以及测试的结 果；在控制连接建立并传递了测试配置信息以后，client与server之间会再建立一个测试连接，用来来回传递着特殊的流量模式，以测试网络的性能。


#5	基准测试工具套件
-------



| 工具 | 描述 |
|:---:|:----:|
| Phoronix Test Suite | 知名评测机构 `Phoronix` 提供的 `linux` 平台测试套件 |
| perf | Linux内核中的系统性能调优工具, Perf Event 是一款随 Linux 内核代码一同发布和维护的性能诊断工具，由内核社区维护和发展。Perf 不仅可以用于应用程序的性能统计分析，也可以应用于内核代码的性能统计和分析。得益于其优秀的体系结构设计，越来越多的新功能被加入 Perf，使其已经成为一个多功能的性能统计工具集 。在第一部分，将介绍 Perf 在应用程序开发上的应用 |
| rt-tests | "Cyclictest is a high resolution test program, written by User:Tglx, maintained by User:Clark Williams", 也就是它是一个高精度的测试程序, `Cyclictest` 是 `rt-tests` 下的一个测试工具, 也是 `rt-tests` 下使用最广泛的测试工具, 一般主要用来测试使用内核的延迟, 从而判断内核的实时性. |


##5.1	phoronix.com
-------

`phoronix.com` 是业内一个知名的网站，其经常发布硬件性能测评以及 `Linux` 系统相关的性能测评, `Phoronix Test Suite` 为该网站旗下的 `linux` 平台测试套件, `Phoronix` 测试套件遵循 `GNU GPLv3` 协议. `Phoronix Test Suite` 默认是通过命令行来的进行测试的, 但也可以调用`GUI`, `Phoronix　Test Suite` 还提供了上传测试结果的服务，也就说你可以把你的测试结果上传在网上，从而可以和别的 `Linux` 用户测出来的结果进行对比.

##5.2 内核中的Perf
-------

`Perf` 是用来进行软件性能分析的工具.

通过它, 应用程序可以利用 `PMU, tracepoint` 和内核中的特殊计数器来进行性能统计. 它不但可以分析指定应用程序的性能问题 (`per thread`), 也可以用来分析内核的性能问题, 当然也可以同时分析应用代码和内核, 从而全面理解应用程序中的性能瓶颈.

最初的时候, 它叫做 `Performance counter`, 在 `2.6.31` 中第一次亮相. 此后他成为内核开发最为活跃的一个领域. 在 `2.6.32` 中它正式改名为 `Performance Event`, 因为 `perf` 已不再仅仅作为 `PMU` 的抽象, 而是能够处理所有的性能相关的事件.

使用 `perf`, 您可以分析程序运行期间发生的硬件事件. 比如 `instructions retired`, `processor clock cycles` 等; 您也可以分析软件事件, 比如 `Page Fault` 和进程切换.

这使得 `Perf` 拥有了众多的性能分析能力. 举例来说, 使用 `Perf` 可以计算每个时钟周期内的指令数, 称为 `IPC`, `IPC` 偏低表明代码没有很好地利用 `CPU`. `Perf` 还可以对程序进行函数级别的采样, 从而了解程序的性能瓶颈究竟在哪里等等. `Perf` 还可以替代 `strace`, 可以添加动态内核 `probe` 点, 还可以做 `benchmark` 衡量调度器的好坏.

人们或许会称它为进行性能分析的"瑞士军刀" 和 "倚天剑".


##5.3 rt-tests
-------


cyclictest测试内核的性能, 包括了 `hackbench`, `cyclictest` 等多个 `benchmark` 工具

[Cyclictest的维基主页](https://rt.wiki.kernel.org/index.php/Cyclictest)这么介绍它“Cyclictest is a high resolution test program, written by User:Tglx, maintained by User:Clark Williams ”，也就是它是一个高精度的测试程序，`Cyclictest` 是 `rt-tests` 下的一个测试工具，也是rt-tests 下使用最广泛的测试工具，一般主要用来测试使用内核的延迟，从而判断内核的实时性。

[cyclictest 简介以及安装](http://blog.csdn.net/longerzone/article/details/16897655)

[cyclictest 的使用](http://blog.csdn.net/ganggexiongqi/article/details/5841347)


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢.
<br>