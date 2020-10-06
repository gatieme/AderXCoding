---

title: Linux(Ubuntu/CentOS) 下查看 GLIBC 版本
date: 2020-10-06 23:35
author: gatieme
tags: linux
categories:
        - linux
thumbnail:
blogexcerpt: 之前在工作中, 经常有同事问我怎么知道当前系统中 GLIBC 的版本号是多少. 今天安装软件的时候, 想到了这个问题, 于是记录下, 与大家共勉.

---


| 日期 | 作者 | GitHub| CSDN | BLOG |
| ------- |:-------:|:-------:|:-------:|:-------:|
| 2020-10-06 | [gatieme](https://blog.csdn.net/gatieme) | [AderXCoding](https://github.com/gatieme/AderXCoding/tree/master/system/tools/glibc/001-version) | [Linux(Ubuntu/CentOS) 下查看 GLIBC 版本](https://blog.csdn.net/gatieme/article/details/108945425) | [Linux(Ubuntu/CentOS) 下查看 GLIBC 版本](https://oskernellab.com/2020/10/06/2020/1006-0001-Linux_get_glibc_version/)|


<br>



本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>

因本人技术水平和知识面有限, 内容如有纰漏或者需要修正的地方, 欢迎大家指正, 鄙人在此谢谢啦

**转载请务必注明出处, 谢谢, 不胜感激**

<br>



# 1 ldd --version
------

最简单直接的方法

```cpp
ldd --version
```
其输出如下:


![001-ldd_version.png](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/glibc/001-version/001-ldd_version.png)

# 2 通过 libc.so 获取版本号
-------

GLIBC 库已经为了我们考虑到这点了, 因此从 libc.so 我们可以获取到版本信息.


## 2.1 首先查找到 libc 库的位置
-------

关于如何找到 GLIBC 库, 有多种方法
1.    ldd 一个当前系统中 C 库编写的动态可执行程序

```cpp
ldd `which top` | grep "libc.so"
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f6e32226000)
```

![002-01-libc_ldd.png](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/glibc/001-version/002-01-libc_ldd.png)

2.    原理同 2, 只不过是从正在运行的程序的动态库中获取

当前进程 shell 一般是一个 C 库的程序, lsof 查看它运行时加载的 libc 库是哪个

```cpp
lsof -p $$ 2>&1 | grep "libc-"
```

![002-02-libc_lsof.png](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/glibc/001-version/002-02-libc_lsof.png)

3.  通过 gcc 获取到 libc 库的位置

cat `gcc -print-file-name=libc.so`

![002-03-libc_gcc.png](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/glibc/001-version/002-03-libc_gcc.png)

## 2.2 从 libc 库上获取版本号
-------

1.    直接看 libc.so 的后缀版本号

很明显, libc-2.27.so 后缀为 2.27, 因此 GLIBC 版本号为 2.27

![002-11-libc_str.png](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/glibc/001-version/002-11-libc_str.png)


2.    直接运行 libc.so

GLIBC 的动态库是可以执行运行的, 运行将显示版本号以及版权信息, 可以看到 版本号也是  2.27

![002-12-libc_run.png](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/glibc/001-version/002-12-libc_run.png)

3.    同 2, 获取版本号

GLIBC 库加上 --version 同样显示版本号, 我们可以看到打印的信息和直接运行的信息是一致的.

![002-13-libc_version.png](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/glibc/001-version/002-13-libc_version.png)


# 3 GNU_LIBC_VERSION
-------

标记 GLIBC 版本号的变量为 GNU_LIBC_VERSION, 直接查看它即可

```cpp
getconf GNU_LIBC_VERSION
```

![003-GNU_LIBC_VERSION.png](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/glibc/001-version/003-GNU_LIBC_VERSION.png)


注意我们还有另外一个变量, 也可以类似的获取到 GLIBC PTHREAD 版本号, GNU_LIBPTHREAD_VERSION, 不过多数情况下, 他与 GLIBC 版本号是一致的.

```cpp
getconf GNU_LIBPTHREAD_VERSION
```

![003-GNU_LIBPTHREAD_VERSION.png](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/glibc/001-version/003-GNU_LIBPTHREAD_VERSION.png)


> 在 Linux 上实现 pThreads 的 NPTL 项目是一个单独的项目, 最初添加内核支持并提供自己的库. 当它足够稳定时, 就会合并为glibc.
> 我们发行版一般使用的 GLIBC 都是 stable 版本, 因此我认为这两个版本在所有合理的最新安装上都是相同的.



# 4 gnu_get_libc_version
-------

GLIBC 中内置了一些信息标记版本号, 用来在程序中可以获取到 GLIBC 的版本号. 这是一个字符串, 因为一些高级的特性是 GLIBC 高版本才支持的, 因此用户的程序可能经常要看版本号来执行不同的操作和处理.
gnu_get_libc_version 和 gnu_get_libc_release 就是这样的内置信息, 我们可以通过  man 手册来获取详细信息.


```cpp
// cat get_glibc_version.c
#include <gnu/libc-version.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
        printf("GNU libc version: %s\n", gnu_get_libc_version());
        printf("GNU libc release: %s\n", gnu_get_libc_release());

        return EXIT_SUCCESS;
}
```


![004-gnu_get_libc_version.png](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/glibc/001-version/004-gnu_get_libc_version.png)

# 5 查看发行版安装的软件包版本
-------

发行版打包的软件包一般都是有版本号后缀的, 因此查看我们发行版安装的 GLIBC 包的名字, 就可以知道版本号.

比如 `Ubuntu` 可以使用 `dpkg -l` 查看安装的软件版本
![在这里插入图片描述](https://img-blog.csdnimg.cn/20201007000719559.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2dhdGllbWU=,size_16,color_FFFFFF,t_70#pic_center)


![005-ubuntu_dpkg.png](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/glibc/001-version/005-ubuntu_dpkg.png)


同样 Centos 也可以使用 rpm -q glibc 查看对应软件包的名称及版本.

# 6 参考资料
-------

[Linux: Check the glibc version](https://benohead.com/blog/2015/01/28/linux-check-glibc-version)



<br>

*   本作品/博文 ( [AderStep-紫夜阑珊-青伶巷草 Copyright ©2013-2017](http://blog.csdn.net/gatieme) ), 由 [成坚(gatieme)](http://blog.csdn.net/gatieme) 创作.

*   采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可. 欢迎转载、使用、重新发布, 但务必保留文章署名[成坚gatieme](http://blog.csdn.net/gatieme) ( 包含链接: http://blog.csdn.net/gatieme ), 不得用于商业目的.

*   基于本文修改后的作品务必以相同的许可发布. 如有任何疑问，请与我联系.

*   **转载请务必注明出处, 谢谢, 不胜感激**
<br>