GDB实用插件(peda, gef, gdbinit)全解
=======

| CSDN | GitHub |
|:----:|:------:|
| [GDB实用插件(peda, gef, gdbinit)全解](http://blog.csdn.net/gatieme/article/details/63254211) | [`AderXCoding/system/tools/gdb/plugin`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/gdb/plugin) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作
<br>


#1	GDB插件配置与实用.gdbinit
-------



当 `GDB` (即 `GNU Project Debugger`)启动时, 它在当前用户的主目录中寻找一个名为 `.gdbinit` 的文件; 如果该文件存在, 则 `GDB` 就执行该文件中的所有命令. 通常, 该文件用于简单的配置命令, 如设置所需的缺省汇编程序格式(`Intel®` 或 `Motorola`) 或用于显示输入和输出数据的缺省基数(十进制或十六进制). 它还可以读取宏编码语言, 从而允许实现更强大的自定义. 该语言遵循如下基本格式：

```cpp

define <command>
<code>
end
document <command>
<help text>
end
```

本文并不详细说明 `.gdbinit` 的语法, 我们只是提供一些从各路大神摘来的配置信息.


`.gdbinit` 的配置繁琐, 因此某些大神想到了用插件的方式来实现, 通过 `Python` 的脚本可以很方便的实现我们需要的功能

>  约定,　本文提供了多种插件, 因此本文选择了一种统一的方式来管理插件
>  在　｀$HOME/.gdb-plugins｀　下为每种脚本依次建立子目录

#2	`gdb` 插件和配置信息
-------


##2.1	peda
-------

项目　　https://github.com/longld/peda


安装

```cpp
git clone https://github.com/longld/peda.git ~/peda
echo "source ~/peda/peda.py" >> ~/.gdbinit
```

其实就是下载完成后, 将 `source ~/peda/peda.py` 写入 `~/.gdbinit`

![peda](peda.png)


##2.2	gef插件
-------

地址 https://github.com/hugsy/gef

安装

```cpp
# via the install script
#下载 `gef.sh` 并执行
wget -q -O- https://github.com/hugsy/gef/raw/master/gef.sh | sh

# manually
# 下载 `gef.py`, 并将其 `source` 写入 `.gdbinit`
wget -q -O ~/.gdbinit-gef.py https://github.com/hugsy/gef/raw/master/gef.py
echo source ~/.gdbinit-gef.py >> ~/.gdbinit
```

可见 `gef.sh` 的工作其实就是将 `gef.py`下载下来, 并将环境变量写入 `.gdbinit`

![gef](gef.png)

##2.3 gdbinit配置信息
-------

我们也可以从网上或自己编写 `.gdbinit` 配置文件, 我们从网上找到一份配置

地址	https://github.com/gdbinit/Gdbinit


安装
```
git clone git@github.com:gdbinit/Gdbinit.git
cp Gdbinit/gdbinit ~/.gdbinit
```

或者

```
wget https://raw.githubusercontent.com/gdbinit/Gdbinit/master/gdbinit
cp gbdinit ~/.gdbinit
```

![Gdbinit](gdbinit.png)



#3	总结
-------

我把前面三个项目组合在一起

地址 : https://github.com/gatieme/GdbPlugins

```cpp
git clone git@github.com:gatieme/GdbPlugins.git ~/.GdbPlugins
```

使用

```cpp
# 使用 peda
echo "source ~/.GdbPlugins/peda/peda.py" > ~/.gdbinit

# 使用 gef
echo "source ~/.GdbPlugins/gef/gef.py" > ~/.gdbinit

#使用 gdbinit
echo "source ~/.GdbPlugins/gdbinit/gdbinit" > ~/.gdbinit
```





#4	参考
-------


[CTF工具集合安装脚本操作姿势](http://www.freebuf.com/sectool/94235.html)

[gdb插件gef安装爬坑](http://www.cnblogs.com/0xmuhe/p/5627172.html)

http://www.cjjjs.com/paper/czxt/20161215202120669.html

[27款反汇编/调试器/静态和动态分析工具](http://tech.it168.com/a2017/0124/3095/000003095000.shtml)


<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作.


