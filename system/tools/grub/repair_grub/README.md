Grub引导项修复
=======

| CSDN | GitHub |
|:----:|:------:|
| [Grub引导项修复详解](http://blog.csdn.net/gatieme/article/details/59127020) | [`AderXCoding/system/tools/repair_boot`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/repair_boot) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处
<br>


#1	Grub丢失Ubuntu引导项修复
-------

GRUB是大多数Linux系统默认使用的引导程序, 可以通过启动菜单的方式选择进入不同的操作系统(如果有的话).

当 "/boot/grub/grub.conf" 配置文件丢失, 或者关键配置出现错误, 或者`MBR`记录中的引导程序遭到破坏时, Linux主机启动后可能只会出现“grub>”的提示符，无法完成进一步的系统启动过程.

```cpp
error : unknow filesystem
grub rescue>
```

的字样, 系统就是进不去.

这表示你的grub2的配置文件损坏, Grub找不到Ubuntu系统的引导项. 从而进入修复模式了(`grub rescue`), 也称**救援模式**.

在救援模式下只有很少的命令可以用: set, ls, insmod, root, prefix

| 命令 | 描述 |
|:---:|:----:|
| set | 查看环境变量，这里可以查看启动路径和分区 |
| ls | 查看设备 |
| insmod | 加载模块 |
| root |指定用于启动系统的分区,在救援模式下设置grub启动分区 |
| prefix | 设定grub启动路径 |

具体修复步骤如下：

##1.1	查看分区

```cpp
grub rescue> ls

列出磁盘分区

(hd0) (hd0,msdos9) (hd0,msdos8) (hd0,msdos7) (hd0,msdos6) (hd0,msdos5) (hd0,msdos2) (hd0,msdos1)
```


>注 : 上面是我的分区设备, 每个人可能不一样, 但原理都是一样的.

##1.2	寻找ubuntu所在分区
就是寻找你的Linux系统是装在以上哪个分区里

```cpp
grub rescue> ls (hd0,msdos1)/
```

*	若出现unknown filesystem字样，则尝试下一个


*	若出现的是你的ubuntu主文件夹下的文件夹和文件的名字，那就是的要找的分区了。




##1.3   安装MBR
-------

###1.3.1	简易安装
-------

```cpp
grub> root (hd0,msdos8)

指定Ubuntu系统根分区所在第一块硬盘中的位置, 具体的分区数字根据你的实际情况来决定.

grub> setup (hd0)
#安装GRUB到硬盘Ubuntu所在磁盘的FBR区中

#退出GRUB安装模式。

grub> cd

#重新引导系统
reboot
```


##1.3.2	安装MBR的详细设置
-------


*	参见

[Linux系统中修复GRUB引导故障手动引导进入操作系统](http://blog.csdn.net/lsbhjshyn/article/details/17752681)


*	修改启动分区


假如你找到的启动分区是 `(hd0,msdos8)`

```cpp
grub rescue>root=(hd0,msdos8)
grub rescue>prefix=/boot/grub                 //grub路径设置
grub rescue>set root=(hd0,msdos8)
grub rescue>set prefix=(hd0,msdos8)/boot/grub
grub rescue>insmod normal                     //启动normal启动
grub rescue>normal
```

之后你就会看到熟悉的启动菜单栏了

*	进入命令行启动ubuntu


进入系统启动选项界面后还是进不去, 因为你还没有真正的修改grub, 这个要到ubuntu里修改

进入系统启动项界面后，按C进入命令行模式

```cpp
grub >set root=hd0,msdos8
grub >set prefix=(hd0,msdos8)/boot/grub
grub >linux /vmlinuz-xxx-xxx root=/dev/sda8 //里边的xxxx可以按Tab键，如果有acpi问题,在最后加一句acpi=off
grub >initrd /initrd.img-xxx-xxx
grub >boot
```

这样就可以进入了

#1.4	进入ubuntu修复grub
-------


其实前面的操作, 已经恢复了MBR了, 我们进入Ubuntu后, 可以更新下`GRUB`引导项, 在终端里运行


```cpp
sudo update-grub
sudo grub-install /dev/sda
```


#2	使用LiveCD通过急救模式恢复或重新安装GRUB
-------

前一种方法的前提是`Grub`引导依旧可以使用, 只是丢失了`Ubuntu`的引导项, 而如果我们的`Grub`都已经损毁或者丢失, 则需要使用光盘镜像进入一个可以使用或者修复的Linux系统来完成GRUB的重新安装.


把系统光盘放入光驱, 重启 `Linux` 系统. 系统启动时按"F2"键, 在"boot:" 提示符下输入 "linuxrescue" 后"回车", 进入"急救模式"引导光盘中的`Linux`系统.

之后依次按回车键接收默认的语言、键盘格式，提示是否配置网卡是一般选择“NO”，然后系统会自动查找硬盘中的Linux分区并尝试将其挂载到"/mnt/sysimage"目录(选择"Continue"确认并继续).

接下来需要特别注意 : 当出现是否初始化磁盘的警告窗口时，一定要选择"NO", 以免对硬盘数据造成进一步损坏. 最后选择"OK"确认后将进入到带"sh-x.x#"提示符的`Bash Shell`环境。


> 注意, 不进入恢复模式, 也可以选择镜像中的"使用Ubuntu"选项, 也会进入光盘中的Linux, 但是不会尝试挂载磁盘, 这个时候我们可以选择手动挂载.

*	如果MBR扇区引导程序没有被损坏, 确认待修复的Linux系统分区的挂载情况, 并重修 `grub.conf`文件.

*	如果MBR扇区引导程序被损坏，即使重建grub.conf配置文件后仍然无法启动系统。这时可以在急救模式的shell环境中使用`grub-install`重新安装`grub`


下面我们着重讲讲第二种情况, 第一种情况下如果不会修改grub.conf文件, 可以使用第二种情况的方法处理


选择Ubuntu安装磁盘, 如果不确定具体在哪个磁盘, 可以用命令查看一下

```cpp
sudo fdisk -l
```

挂载Ubuntu系统安装磁盘(我的是在第0磁盘，故为sda0)

```cpp
sudo mount /dev/sda0 /mnt
```
开始恢复grub2系统引导

```cpp
sudo grub-install --root-directory=/mnt/dev/sda
```

执行命令之后, 如果没有报错, 则恢复成功, 重启即可.


恢复之后是之前的系统引导界面，如果新安装的系统没有在界面上显示，那么可以进入Ubuntu系统，进行grub/grub2更新

打开终端，输入


```cpp
sudo update-grub2
```

grub2请使用


```cpp
sudo update-grub2
```

<br>
<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可

