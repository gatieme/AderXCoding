AderXCoding
=======

| CSDN | GitHub |
|:----:|:------:|
| [Aderstep--紫夜阑珊-青伶巷草](http://blog.csdn.net/gatieme) | [`AderXCoding/system/tools`](https://github.com/gatieme/AderXCoding/tree/master/system/tools) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处
<br>


| Benchmark | 地址 |
|:---------:|:---:|
| PARSEC | http://parsec.cs.princeton.edu |
| Splash | http://www.capsl.udel.edu/splash/Download.html |


http://blog.csdn.net/xf_xjtu/article/details/7916547

http://liuyix.org/splash2-benchmark/

SPLASH2
1992年，斯坦福大学推出了Stanford ParalleL Applications for SHared memory(SPLASH)，1995年SPLASH第二版问世，被称为SPLASH-2。SPLASH-2使用C语言，由12个程序组成，使用PThread并行方式。

SPLASH-2包含4个核心程序：

Cholesky:用于将一个稀疏矩阵拆分成一个下三角矩阵和它的转置的积；
FFT：用于计算快速傅里叶变换；
Radix：是分配存储地址的算法；
LU：用于将一个稀疏矩阵拆分成一个下三角矩阵和一个上三角矩阵的积
另外还包含：

Ocean：用于通过海洋的边缘的海流模拟整个海洋的运动；
Radiosity：用于模拟光线在不同场景下的光影现象；
Barnes： 用于模拟一个三维多体系统（例如星系）；
Raytrace：用于模拟光线的路径；
以及BARNS、FMM、Volrend、Water-Nsquared总共8个其他应用程序。

然而，SPLASH2确实太老了。其官方主页www-flash.stanford.edu/apps/SPLASH根本无法打开。以至没啥更好的资料。甚至连原始的SPLASH2程序都下载不了，好在http://kbarr.NET/splash2上找到个作者提供的，解压时会提示一定问题，但是无关痛痒不影响使用。我这里也提供一份本地下载。

 

The Modified SPLASH-2
改善旧的SPLASH2，使其使用更现代的编程方法。具体的就是使用新版Pthread的一些并行编程方法，如Barrier。具体的更改可以看http://www.capsl.udel.edu/splash/ChangeLog.html。

使用方法：

下载原始SPLASH-2包，(地址见上文). 并解压到相应目录。
下载补丁。网址：http://www.capsl.udel.edu/splash/Download.html，本地下载,将它放入SPLASH-2解压后的目录中，并解压缩。
打补丁。命令：patch -p1<splash2-modified.patch
删除补丁文件splash2-modified.patch.
按照具体情况编辑splash2/codes/Makefile.config文件，尤其要检查里面关于splash程序包的路径是否正确。
在splash2/codes/null_macro文件夹中有三个宏：c.m4.null,c.m4.null.POSIX,c.mu.null.POSIX_BARRIER,具体选用哪个宏，在Makefile中指定。
其中第一个宏是将程序串行执行。后面两个都是支持并行运行的，其中最后一个支持栅栏同步。

命令：make开始对每个程序进行编译。
注意：其它的程序通过make编译良好，但在apps中有一个radiosity在编译时，必须先编译它下面的两个子文件夹。
其中每个分程序的运行都可以使用-h选项来查看需要哪些参数。例如 FFT –h,就可以得到如下结果：
Command line options:                                                 

-mM : M = even integer; 2**M total complex data points transformed.  

-pP : P = number of processors; Must be a power of 2.                 

-nN : N = number of cache lines.                                    

-lL : L = Log base 2 of cache line length in bytes.                 

-s : Print individual processor timing statistics.                 

-t : Perform FFT and inverse FFT. Test output by comparing the    

integral of the original data to the integral of the data     

that results from performing the FFT and inverse FFT.        

-o : Print out complex data points.                               

-h : Print out command line options.        

SPLASH-2有四个内核程序和8个应用程序。其中应用程序在运行的时候，必须在命令后加上输入文件，里面有样本范例。





<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
<br>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可


http://www.davidhill.co/2012/02/enable-esxi-shell-vsphere-5-0/


https://zhidao.baidu.com/question/583512262.html

http://blog.csdn.net/yumushui/article/details/38776603