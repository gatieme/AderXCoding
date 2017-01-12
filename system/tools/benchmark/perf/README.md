AderXCoding
=======

| CSDN | GitHub |
|:----:|:------:|
| [Aderstep--紫夜阑珊-青伶巷草](http://blog.csdn.net/gatieme) | [`AderXCoding/system/tools`](https://github.com/gatieme/AderXCoding/tree/master/system/tools) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢.
<br>



`Perf Event` 是一款随 `Linux` 内核代码一同发布和维护的性能诊断工具，由内核社区维护和发展。`Perf` 不仅可以用于应用程序的性能统计分析，也可以应用于内核代码的性能统计和分析。得益于其优秀的体系结构设计，越来越多的新功能被加入 `Perf`，使其已经成为一个多功能的性能统计工具集 。在第一部分，将介绍 Perf 在应用程序开发上的应用。


#1	`Perf` 简介
-------

`Perf` 是用来进行软件性能分析的工具
通过它，应用程序可以利用 `PMU`, `tracepoint` 和内核中的特殊计数器来进行性能统计。它不但可以分析指定应用程序的性能问题 (`per thread`)，也可以用来分析内核的性能问题，当然也可以同时分析应用代码和内核，从而全面理解应用程序中的性能瓶颈。

最初的时候，它叫做 `Performance counter`，在 `2.6.31` 中第一次亮相。此后他成为内核开发最为活跃的一个领域。在 2.6.32 中它正式改名为 Performance Event，因为 perf 已不再仅仅作为 PMU 的抽象，而是能够处理所有的性能相关的事件。
使用 perf，您可以分析程序运行期间发生的硬件事件，比如 instructions retired ，processor clock cycles 等；您也可以分析软件事件，比如 Page Fault 和进程切换。
这使得 Perf 拥有了众多的性能分析能力，举例来说，使用 Perf 可以计算每个时钟周期内的指令数，称为 IPC，IPC 偏低表明代码没有很好地利用 CPU。Perf 还可以对程序进行函数级别的采样，从而了解程序的性能瓶颈究竟在哪里等等。Perf 还可以替代 strace，可以添加动态内核 probe 点，还可以做 benchmark 衡量调度器的好坏。。。
人们或许会称它为进行性能分析的“瑞士军刀”，但我不喜欢这个比喻，我觉得 perf 应该是一把世间少有的倚天剑。
金庸笔下的很多人都有对宝刀的癖好，即便本领低微不配拥有，但是喜欢，便无可奈何。我恐怕正如这些人一样，因此进了酒馆客栈，见到相熟或者不相熟的人，就要兴冲冲地要讲讲那倚天剑的故事。



http://www.ibm.com/developerworks/cn/linux/l-cn-perf1/
http://www.ibm.com/developerworks/cn/linux/l-cn-perf2/

[How to compile a Ubuntu Maverick 2.6.35 kernel for Lucid](http://blog.avirtualhome.com/how-to-compile-a-ubuntu-2-6-35-kernel-for-lucid/)

[ANDROID ON INTEL ARCHITECTUREperf for Android](http://blog.chinaunix.net/uid-7179692-id-3757828.html)

[Redhat Enterprise 4.3中静态编译perf](http://blog.csdn.net/justlinux2010/article/details/15340261)

[Subject: [beagleboard] Cross Compile of perf not working](http://git.net/ml/beagleboard/2013-02/msg00175.html)

[perf Examples](http://www.brendangregg.com/perf.html)
http://www.thinkwiki.org/wiki/How_to_use_cpufrequtils

http://blog.csdn.net/zhangskd/article/details/37902159


<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
<br>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可


http://www.davidhill.co/2012/02/enable-esxi-shell-vsphere-5-0/


https://zhidao.baidu.com/question/583512262.html

http://blog.csdn.net/yumushui/article/details/38776603
