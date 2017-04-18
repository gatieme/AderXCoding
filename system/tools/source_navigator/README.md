linux下搜狗输入法不能输入中文的解决方案
=======

| CSDN | GitHub |
|:----:|:------:|
| [linux 下搜狗输入法不能输入中文的解决方案](http://blog.csdn.net/gatieme/article/details/68947995) | [`AderXCoding/system/tools/sougoupinyin`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/sougoupinyin) |


http://blog.csdn.net/qq_36355662/article/details/62887174

<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作
<br>

大家知道 `Windows` 下有一个很好的查看源代码的软件 `sourceinsight`, 使用 `source insight` 查看 `Linux` 内核代码、嵌入式软件开发中的C语言项目源代码、驱动程序代码很是方便.

在 `Linux` 下使用 `vim` 查看源代码不是很方便, 于是搜了一下 `Linux` 下 `sourceinsight` 的相关替代软件, 找到了一款 `Source Navigator`, 于是就试着在 `Ubuntu` 下安装了一下.

在 `ubuntu`中安装 `Source-Navigator` 及使用手册
Ubuntu 12.10安装Source Navigator

#1	安装sourcenavigator-NG4.5软件
-------

*	下载源码包

[点击这里](https://sourceforge.net/projects/sourcenav/files/NG4.5/sourcenavigator-NG4.5.tar.bz2/download)下载最新的源码包, 我下载的是 `sourcenavigator-NG4.5.tar.bz2`

```cpp
tar -xjvf sourcenavigator-NG4.5.tar.bz2
```

*	源码编译安装sourcenavigator-NG4.5

通过查看解压之后的 `sourcenavigator-NG4.5` 目录下的`INSTALL`文件, 可以看到安装的方法

```cpp
./configure --prefix=/opt/sourcenav
make
sudo make install
```

*	配置环境变量

安装好 `sourcenavigator-NG4.5` 之后修改 `/etc/environment`配置文件, 或者 `bashrc` 等文件


在 `PATH` 环境变量之后追加 `sourcenavigator-NG4.5` 安装后的 `bin`目录

*	启动snavigator

键入命令: `snavigator`, 就可以启动了.

不过前提是要将 `/opt/sourcenav/bin` 目录下的`snavigator` 等 `tool` 工具添加到 `PATH` 环境变量中去, 不然系统无法识别.



<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作.
