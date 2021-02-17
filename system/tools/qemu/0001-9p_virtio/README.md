---

title: qemu中使用 9p virtio, 支持 host 和 guest 中共享目录
date: 2018-09-30 19:46
author: gatieme
tags: 
	- qemu
categories:
        - 编程珠玑
thumbnail: 
blogexcerpt: 在使用qemu调试内核的时候, 如果没有网络，想要部署点驱动或者程序上去都需要重新制作文件系统，本文讲解了如何通过 9p virtio fs 实现在 qemu 和 host 机器上共享文件和目录。

---

| CSDN | GitHub | Hexo |
|:----:|:------:|:----:|
| [qemu中使用 9p virtio, 支持 host 和 guest 中共享目录](https://blog.csdn.net/gatieme/article/details/82912921) | [`AderXCoding/system/tools/qemu/0001-9p_virtio`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/qemu/0001-9p_virtio) | [gatieme.github.io](https://gatieme.github.io) |

<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>

本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作

因本人技术水平和知识面有限, 内容如有纰漏或者需要修正的地方, 欢迎大家指正, 也欢迎大家提供一些其他好的调试工具以供收录, 鄙人在此谢谢啦

<br>


#1	问题描述
-------

使用 qemu 调试内核是很方便的，但是我们有时候想传点驱动或者程序上去跑一下子，都需要重新制作和打包文件系统，这样花费了我们的精力，也很烦。

那有没有什么办法能够在 qemu 和 host 机器之间共享文件呢，这样我们就省去了很多工作量。

> 于是 9p virtio fs 就登场了

#2	问题分析
-------

`9p` 是啥，网络文件系统，用于共享目录。当然，qemu中使用9p是用于host和guest中共享目录，也不需要网络的支持，而是需要virtio的支持。

#3	qemu 使用 9p virtio实现共享目录
-------

##3.1	`qemu` 支持和设置 `virtfs`
-------

###3.1.1	`qemu` 启动参数添加 `virfts`
-------

`qemu` 启动参数需要添加 :

```cpp
-fsdev local,security_model=passthrough,id=fsdev0,path=/tmp/share \
-device virtio-9p-pci,id=fs0,fsdev=fsdev0,mount_tag=hostshare
```

其中 `path` 为 `host` 本地的共享目录

然后提示：

```cpp
'virtio-9p-pci' is not a valid device model name
```

需要重新编译 `qemu`, 编译时添加额外的 `configure` 参数 `--enable-virtfs`


###3.1.2	`qemu` 支持 `virtfs`
-------


```cpp
./configure --enable-kvm --enable-virtfs --prefix=/opt/software/toolchain/qemu
```

注意 `qemu` 支持 `virtfs` 需要 `libcap` 和 `libattr` 等依赖库.


```
./configure --enable-kvm --enable-virtfs --prefix=/opt/software/toolchain/qemu                            !2818

ERROR: VirtFS requires libcap devel and libattr devel
```

`CentOS` 可以使用如下命令安装

```cpp
sudo yum install -y libcap-devel
sudo yum install -y libattr-devel
```

编译安装 `qemu` 后, 再运行, 可以了.


##3.2	`guest` 支持和设置 `virtfs`
-------

###3.2.1	在 `guest` 中挂载 `host` 共享的目录
-------

```cpp
mkdir /tmp/host_files
mount -t 9p -o trans=virtio,version=9p2000.L hostshare /tmp/host_files
```

如果提示 :

```cpp
mount: unknown filesystem type '9p'
```

则说明构建的 `guest` 内核不支持 `9p-virtio`.
需要开启对应的内核选项, 并重新编译.


###3.2.2	需要在 `kernel` 中添加 `9p` 的支持
-------


```cpp
CONFIG_NET_9P=y
CONFIG_9P_FS=y
CONFIG_VIRTIO_PCI=y
CONFIG_NET_9P_VIRTIO=y
CONFIG_9P_FS_POSIX_ACL=y
CONFIG_NET_9P_DEBUG=y (Optional可选)
```

然后就可以使用了, 如果再加上 `virtio console` 的支持, 那么既有 `shell`, 又可以传输文件
基本可以代替 `adb` 的常用功能了.


最后, 一切就绪之后, 启动 qemu, 就可以看到目录正常挂载了.

host 机器的共享目录

![host 机器的共享目录](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/qemu/0001-9p_virtio/001-9p_virtio_host.png)

guest 机器的挂载点

![guest 机器的挂载点](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/qemu/0001-9p_virtio/002-9p_virtio_guest.png)


#4	参考
-------

[qemu启动命令](http://www.linux-kvm.org/page/9p_virtio)

[kernel配置](http://wiki.qemu.org/Documentation/9psetup)

[qemu添加configure选项](https://groups.google.com/forum/#!topic/coreos-dev/MjhL3tOOAVM)

[qemu中使用9p，支持host和guest中共享目录](https://blog.csdn.net/ayu_ag/article/details/52956351)

[Qemu share folder - 9pnet_virtio: no channels available for device](https://superuser.com/questions/1317119/qemu-share-folder-9pnet-virtio-no-channels-available-for-device)

[Documentation/9psetup](https://wiki.qemu.org/Documentation/9psetup)

[Linux-KVM-9P_virtio](https://www.linux-kvm.org/page/9p_virtio)

<br>

*	本作品/博文 ( [AderStep-紫夜阑珊-青伶巷草 Copyright ©2013-2017](http://blog.csdn.net/gatieme) ), 由 [成坚(gatieme)](http://blog.csdn.net/gatieme) 创作.

*	采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可. 欢迎转载、使用、重新发布, 但务必保留文章署名[成坚gatieme](http://blog.csdn.net/gatieme) ( 包含链接: http://blog.csdn.net/gatieme ), 不得用于商业目的. 

*	基于本文修改后的作品务必以相同的许可发布. 如有任何疑问，请与我联系.
