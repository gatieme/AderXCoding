查看linux系统CPU信息的经验
=======

| CSDN | GitHub |
|:----:|:------:|
| [Ubuntu安装开发者中心Ubuntu Make(原Ubuntu Developer Tools Center)](http://blog.csdn.net/gatieme/article/details/52745534) | [`AderXCoding/system/tools/ubuntu_make`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/ubuntu_make) |



http://jingyan.baidu.com/article/6525d4b150b472ac7d2e94a6.html
#1	/proc/cpuinfo
-------


最简单的方法就是查看 `/proc/cpuinfo`, 这个虚拟文件展示的是可用CPU硬件的配置。
通过查看这个文件，你能识别出物理处理器数（插槽）、每个CPU核心数、可用的CPU标志寄存器以及其它东西的数量。


```cpp
cat /proc/cpuinfo
```

![查看linux系统CPU信息]()

#2	cpufreq-info
-------


cpufreq-info命令(cpufrequtils包的一部分)从内核/硬件中收集并报告CPU频率信息。这条命令展示了CPU当前运行的硬件频率，包括CPU所允许的最小/最大频率、CPUfreq策略/统计数据等等。来看下CPU #0上的信息：


查看linux系统CPU信息的经验



#3	cpuid
-------

cpuid命令的功能就相当于一个专用的CPU信息工具，它能通过使用CPUID功能来显示详细的关于CPU硬件的信息。信息报告包括处理器类型/家族、CPU扩展指令集、缓存/TLB（译者注：传输后备缓冲器）配置、电源管理功能等等。
查看linux系统CPU信息的经验
4. dmidecode
dmidecode命令直接从BIOS的DMI（桌面管理接口）数据收集关于系统硬件的具体信息。CPU信息报告包括CPU供应商、版本、CPU标志寄存器、最大/当前的时钟速度、(启用的)核心总数、L1/L2/L3缓存配置等等。
查看linux系统CPU信息的经验
5. hardinfo
hardinfo是一个基于GUI的系统信息工具，它能展示给你一个易于理解的CPU硬件信息的概况，也包括你的系统其它的一些硬件组成部分。
查看linux系统CPU信息的经验
6. i7z
i7z是一个专供英特尔酷睿i3、i5和i7 CPU的实时CPU报告工具。它能实时显示每个核心的各类信息，比如睿频加速状态、CPU频率、CPU电源状态、温度检测等等。i7z运行在基于ncurses的控制台模式或基于QT的GUI的其中之一上。
查看linux系统CPU信息的经验
7. likwid拓扑
likwid (Like I Knew What I'm Doing) 是一个用来测量、配置并显示硬件相关特性的命令行收集工具。其中的likwid拓扑结构能显示CPU硬件(线程/缓存/NUMA)的拓扑结构信息，还能识别处理器家族(比如：Intel Core 2, AMD Shanghai)。
查看linux系统CPU信息的经验
8. lscpu
lscpu命令用一个更加用户友好的格式统计了 /etc/cpuinfo 的内容，比如CPU、核心、套接字、NUMA节点的数量（线上/线下）。
查看linux系统CPU信息的经验
9. lshw
lshw命令是一个综合性硬件查询工具。不同于其它工具，lshw需要root特权才能运行，因为它是在BIOS系统里查询DMI（桌面管理接口）信息。它能报告总核心数和可用核心数，但是会遗漏掉一些信息比如L1/L2/L3缓存配置。GTK版本的lshw-gtk也是可用的。
查看linux系统CPU信息的经验
10. lstopo
lstopo命令 (包括在 hwloc 包中) 以可视化的方式组成 CPU、缓存、内存和I/O设备的拓扑结构。这个命令用来识别处理器结构和系统的NUMA拓扑结构。
查看linux系统CPU信息的经验
11
11. numactl
最初其被开发的目的是为了设置NUMA的时序安排和Linux处理器的内存布局策略，numactl命令也能通过命令行来展示关于CPU硬件的NUMA拓扑结构信息。
查看linux系统CPU信息的经验
12
12. x86info
x86info是一个为了展示基于x86架构的CPU信息的命令行工具。信息报告包括CPU型号、线程/核心数、时钟速度、TLB（传输后备缓冲器）缓存配置、支持的特征标志寄存器等等。
查看linux系统CPU信息的经验