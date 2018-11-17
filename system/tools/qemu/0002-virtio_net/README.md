---

title: qemu中使用 9p virtio, 支持 host 和 guest 中共享目录
date: 2018-09-02 18:40
author: gatieme
tags: qemu
categories:
        - qemu
thumbnail: 
blogexcerpt: 在使用qemu调试内核的时候, 如果没有网络，想要部署点驱动或者程序上去都需要重新制作文件系统，本文讲解了如何通过 9p virtio fs 实现在 qemu 和 host 机器上共享文件和目录。

---

| CSDN | GitHub | Hexo |
|:----:|:------:|:----:|
| [qemu中使用 9p virtio, 支持 host 和 guest 中共享目录](https://blog.csdn.net/gatieme/article/details/82912921) | [`AderXCoding/system/tools/qemu/0001-9p_virtio`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/qemu/0001-9p_virtio) | [KernelShow(gatieme.github.io)](https://gatieme.github.io/2018/09/30/2018/09/0003-qemu_use_9pnet_virtio_fs_to_share_folder/index) | 
<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>

本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作

因本人技术水平和知识面有限, 内容如有纰漏或者需要修正的地方, 欢迎大家指正, 也欢迎大家提供一些其他好的调试工具以供收录, 鄙人在此谢谢啦

<br>

#1	配置 qemu 的网络功能
-------

`qemu` 支持多种网络链接方式

*	默认方式为用户模式网络(Usermode Networking), 数据包由NAT方式通过主机的接口进行传送.

	虚拟机可以使用网络服务, 但局域网中其他机器包括宿主机无法连接它. 比如, 它可以浏览网页, 但外部机器不能访问架设在它里面的 `web` 服务器.
	默认的, 虚拟机得到的 `ip` 空间为 `10.0.2.0/24`, 主机 `ip` 为 `10.0.2.2` 供虚拟机访问. 可以 `ssh` 到主机`(10.0.2.2)`, 用 `scp` 来拷贝文件.

*	使用桥接方式(Bridged Networking), 外部的机器可以直接联通到虚拟机, 就像联通到你的主机一样.

	这种模式允许虚拟机就像一台独立的主机一样拥有网络. 这种模式需要网卡支持, 一般的有线网卡都支持, 绝大部分的无线网卡都不支持.
	优点: VM 可以访问外部的网络, 外部的网络也可以访问 VM
	缺点: 需要给 VM 分配一个外部可见的 IP 地址

#2	配置 qemu 桥接网络
-------

桥接(`bridge`) 模式是最常见的 VM 网络模式.


##2.1	配置 host
-------       

桥接就是把一台机器上的若干个网络接口 连接 起来.
其结果是, 其中一个网口收到的报文会被复制给其他网口并发送出去. 以使得网口之间的报文能够互相转发.

目的：使得局域网内可以通过ssh登陆虚拟机
   
*	首先, 安装两个配置网络所需软件包：    

```cpp
sudo apt-get install bridge-utils        # 虚拟网桥工具
sudo apt-get install uml-utilities       # UML（User-mode linux）工具
```
```

*	tun 设备

桥接模式需要依赖内核的 `tun/tap` 模块的支持.
输入如下命令查看 `/dev/net/tun` 文件 :

```cpp
ll /dev/net/tun

#crw-rw-rw- 1 root root 10, 200 Oct 29 17:44 /dev/net/tun
```

如果该文件存在, 这表明内核已经支持开启了 `tun` 支持
如果该文件不存在, 则需要加载 `tun` 模块，并创建 `/dev/net/tun` 文件.

*	host 配置交换网卡

在 Host 侧需要创建一个软交换机 `br0`, 把 host 侧的物理网卡和一个虚拟网卡(tap0), 添加到这个交换机中.
VM 会使用虚拟网卡(tap0) 来转发来自 VM 的网络报文.

修改 `/etc/network/interfaces` 文件, 添加如下信息:

```cpp
auto br0
iface br0 inet dhcp
bridge_ports eth0
```

我们也可以通过脚本来完成这个工作

```

添加 `/etc/qemu-ifup` 和 `/etc/qemu-ifdown` 脚本.

默认情况下, 当 `qemu` 使用 `tap` 设备时, 会执行 `/etc/qemu-ifup` 和 `/etc/qemu-ifdown` 这两个脚本.

我们需要创建这两个脚本，然后为它们加上可执行权限

创建 `/etc/qemu-ifup` 脚本, 内容如下所示

```cpp
#!/bin/sh

echo sudo tunctl -u $(id -un) -t $1
sudo tunctl -u $(id -un) -t $1

echo sudo ifconfig $1 0.0.0.0 promisc up
sudo ifconfig $1 0.0.0.0 promisc up

echo sudo brctl addif br0 $1
sudo brctl addif br0 $1

echo brctl show
brctl show

sudo ifconfig br0 192.168.7.20
```

创建 `/etc/qemu-ifdown` 脚本, 内容如下所示

```cpp
#!/bin/sh

echo sudo brctl delif br0 $1
sudo brctl delif br0 $1

echo sudo tunctl -d $1
sudo tunctl -d $1
 
echo brctl show
brctl show
```


为 /etc/qemu-ifup 和 /etc/qemu-ifdown 脚本加上可执行权限：

```cpp
chmod +x /etc/qemu-ifup
chmod +x /etc/qemu-ifdown
```

最后需要重启计算机或者服务, 使新的 `/etc/network/interfaces` 配置文件生效.

运行 qemu-mini2440 虚拟机
进入 /home/user/sylixos_workspace/qemu-mini2440 目录：
cd /home/user/sylixos_workspace/qemu-mini2440
输入如下命令执行 nandCreator.sh 脚本：
chmod +x nandCreator.sh
./nandCreator.sh
执行完成后，会在当前目录生成一个名为 nand.bin 的 Nand Flash 镜像文件。
输入如下命令执行 mini2440_run.sh 脚本:
chmod +x mini2440_run.sh
./mini2440_run.sh
mini2440_run.sh 脚本的内容如下：
./qemu-system-arm -M mini2440 -show-cursor -kernel ../bspmini2440/Debug/bspmini2440.bin -serial stdio -mtdblock nand.bin -net nic,vlan=0 -net tap,vlan=0,ifname=tap0

如果出现如下信息：

```cpp
warning: could not configure /dev/net/tun: no virtual network emulation
Could not initialize device 'tap'
```

那么先手动执行如下命令：

```cpp
/etc/qemu-ifup tap0
```

注意：不可使用 sudo 执行上一条命令，每次启动 ubuntu 后都需要手动执行一次上一条命令。




<br>

*	本作品/博文 ( [AderStep-紫夜阑珊-青伶巷草 Copyright ©2013-2017](http://blog.csdn.net/gatieme) ), 由 [成坚(gatieme)](http://blog.csdn.net/gatieme) 创作.

*	采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可. 欢迎转载、使用、重新发布, 但务必保留文章署名[成坚gatieme](http://blog.csdn.net/gatieme) ( 包含链接: http://blog.csdn.net/gatieme ), 不得用于商业目的. 

*	基于本文修改后的作品务必以相同的许可发布. 如有任何疑问，请与我联系.
