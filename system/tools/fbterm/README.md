ubuntu文本模式/终端/tty中文乱码解决(fbterm)
=======

http://blog.csdn.net/xiajian2010/article/details/9625131

http://blog.chinaunix.net/uid-436750-id-2123586.html

https://github.com/jlevy/the-art-of-command-line

http://forum.ubuntu.org.cn/viewtopic.php?f=8&t=382065&start=0

#1	问题
-------


最近在学习linux文本模式下的使用，遇到第一个问题就是在文本模式下中文乱码，自然想到是编码的问题，所以在网上找了一下解决方法，有人的解决方式是以下这样的


1.	Alt+Ctrl+F1 进入第一个终端tty1，发现中文乱码。 

2.	安装zhcon

```cpp
sudo apt-get install zhcon
```

3.	输入下面命令，启动zhcon，中文显示正常。 

```cpp
sudo zhcon --utf8 --drv=vga
```

#2	fbterm解决乱码
-------

##2.1	fbterm介绍
-------


`fbterm`--支持中文显示的控制台

`fbterm`提供了一个快速的终端仿真器, 它直接运行在你的系统中的帧缓冲(`framebuffer`)之上. 使用帧缓冲可以在终端渲染`UTF-8`文本时可以提高性能

`fbterm`旨在提供国际化和现代字体支持时至少与`Linux`内核终端一样快. 它允许你在同一个帧缓冲上创建多达10个不同的终端窗口，每个窗口都有它的回滚历史


##2.2	安装fbterm
-------


```cpp
sudo apt-get install fbterm
```

安装完后, **运行fbterm**

要运行`fbterm`, 首先检查当前用户是否在`video`组, 如不在, 则加入.


```cpp
sudo fbterm
```

当运行`fbterm`后, 会在用户主目录下生成`.fbtermrc`配置文件, 其中可以更换字体样式及大小、默认前/背景色.



若你不能看到中文, 按Ctrl+Alt+E退出后，再运行下面的命令：
```cpp
LANG=zh_CN.utf-8 fbterm
```

默认情况下非root用户不能运行fbterm命令, 因此要执行如下命令

```cpp
gpasswd -a user viedo
```

来使普通用户`user`能成功使用`fbterm`, 然后执行

```cpp
chmod u+s /usr/bin/fbterm
```

**退出fbterm**

在控制台中按`Ctrl + Alt + E`退出


##2.3	配置fbterm
-------

当然`fbterm`功能是很强大的, 支持字体样式、大小、样色设置等，修改配置文件`.fbtermrc`即可，在控制台输入以下命令：

sudo gedit ~/.fbtermrc

打开配置文件内容大致如下，可以根据需要做相应修改保存（然后重新启动fbterm：在控制台输入Ctrl+Alt+E 退出）则可：

