CentOS下支持挂载exFAT与NTFS文件系统
=======

| CSDN | GitHub |
|:----:|:------:|
| [You-Get--基于Python3的开源网络视频下载工具](http://blog.csdn.net/gatieme/article/details/61623891) | [`AderXCoding/system/tools/you-get`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/you-get) |

<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作
<br>

[RHEL/CentOS/Fedora各种源(EPEL、Remi、RPMForge、RPMFusion)配置](http://www.cnblogs.com/mawanglin2008/p/3532247.html)


#1	问题
-------


##1.1	问题描述
-------


给实验室的一台破机器装了 `CentOS 7`, 今天想从移动硬盘上往机器上拷贝点东西, `mount`挂载的时候发现挂载不上去, 提示未知的文件系统. 想了想好像是 `CentOS` 默认是不支持这些 `Windows` 的文件系统的. 这点还是 `Ubuntu` 友好, 包都装好了, 移动硬盘插上去自动挂载, 没办法了, `CentOS`  上折腾吧.

##1.2 Windows下文件系统
-------

`Windows`下分区的常见格式有 `FAT`、`FAT32`、`NTFS` 和 `exFAT`

早期大家见得多的格式一般是`FAT` 和 `FAT32`, 不过目前由于单个文件越来越大,超过 `4G`的文件, `FAT` 和 `FAT32` 格式不支持,所以现在的硬盘格式都会被转换成 `NTFS` 或 `exFAT`格式,

##1.3	NTFS和exFAT分区格式的特点与区别
-------

`NTFS(New Technology File System)` 是 `WindowsNT` 和高级服务器网络操作系统环境的文件系统, 设计的目的是提供比 `FAT32`更高的可靠性, 并消除 `FAT32` 文件系统容量限制. 它除了支持更大的分区和文件、更节约硬盘空间外, 还提供了 `FAT32` 文件系统不能提供的长文件名、压缩分区、事件追踪、文件索引、高容错性、数据保护和恢复以及加密访问等功能.

但是, 为什么闪盘和各种存储卡很少使用 `NTFS` 进行分区呢? 虽然 `NTFS`优点众多, 但它是专为传统机械硬盘而设计的. 它采用了一种"日志式"的文件系统, 需要频繁记录磁盘的详细读写操作, 会给闪盘或 `SSD` 这类储介质带来额外的负担. 同时, `NTFS` 文件系统频繁的读写也影响到闪盘的性能,带来传输速率的下降。

为此,微软在传统FAT 32分区的基础上开发了exFAT文件系统(Extended File Allocation Table FileSystem),既弥补了FAT32的局限性和缺点,又没有NTFS那些会影响闪存寿命的功能,适合各种移动存储卡和闪盘使用。

`exFAT` 文件系统具有如下优点:

*	分区大小和支持的单个文件大小最大可达 `16EB`;

*	使用了剩余空间分配表,空间利用率更高;

*	同一目录下最大文件数可达65536个;

*	支持访问控制。

目前, 只有固态硬盘、闪盘和存储卡才能格式化成 `exFAT`, 传统硬盘是无法格式化成 `exFAT` 格式的,因此它是一种专门针对闪存的文件系统。



#2	支持挂载NTFS文件系统
-------

`exfat` 格式的文件系统是通过 `fuse` (`Filesystem in userspace` ) 模块来支持的

##2.1	安装fuse-exfat
-------


`exfat` 支持是通过 `fuse` 模块的方式支持的, 其项目地址是 :

https://code.google.com/p/exfat/ ，当前版本是 : `1.0.1`
目前exfat的支持已经是全功能支持，支持读写。


###2.1.1	yum源或者rpm包安装
-------

使用如下命令直接从源中安装

```cpp
sudo yum install fuse-exfat
```

如果提示未找着软件包, 说明您未添加 `rpmfusion` 源, 下载[rpmfusion-free-release-7.noarch.rpm](http://download1.rpmfusion.org/free/el/rpmfusion-free-release-7.noarch.rpm)

*	可尝试添加源后, 再安装

*	下载 [`fuse-exfat`包](http://download1.rpmfusion.org/free/el/updates/7/x86_64/f)(必须)和[`exfat-utils`](http://download1.rpmfusion.org/free/el/updates/7/x86_64/e)包直接进行安装

下载地址 [`fuse-exfat-1.0.1-1.el7.x86_64.rpm`](http://download1.rpmfusion.org/free/el/updates/7/x86_64/f/fuse-exfat-1.0.1-1.el7.x86_64.rpm)

下载地址 [`exfat-utils-1.0.1.el7.x86_64.rpm`](http://download1.rpmfusion.org/free/el/updates/7/x86_64/e/exfat-utils-1.0.1-1.el7.x86_64.rpm)


然后直接安装

```cpp
sudo rpm -ivh fuse-exfat-1.0.1-1.el7.x86_64.rpm
sudo rpm -ivh exfat-utils-1.0.1-1.el7.x86_64.rpm
```

###2.1.2	`SRC.RPM` 源码构建 `RPM` 安装
-------

虽然不是想说这种方法, 一般来说, 发行版对于每一个 `rpm` 或者 `deb` 包都会提供其源码包, 方便开发者自行从源码构建安装包, `Ubuntu` 等发行版使用 `apt-get source`下载源码, 使用
 `apt-get build-dep` 构建其环境, `Redhat`等发行版则使用 `RPMBUILD` 来构建, 其包成为`src.rpm`
 
可以下载``src.rpm源代码包, 并自行使用 `scons` 和 `gcc` 编译, 也可以在 `rpmfusion` 下载源代码 `RPM`, 然后通过构建 `RPM` 来安装. 这里采用构建RPM的方式（这样安装卸载都很方便）。

下载地址 :  
http://download1.rpmfusion.org/free/el/updates/6/SRPMS/repoview/index.html

分别下载：fuse-exfat-1.0.1-1-el6.src.rpm 和 exfat-utils-1.0.1-1.el6.src.rpm

http://download1.rpmfusion.org/free/el/updates/7/x86_64/f/


*	编译安装：

编译前，请先检查系统，如果系统中没有scons和gcc，请通过yum安装：

```cpp
sudo yum install scons gcc
```

这个软件是fuse模块，编译需要fuse-devel包支持：


```cpp
sudo yum install fuse-devel
```

下载后，安装源代码RPM：
```cpp
rpm -ivh fuse-exfat-1.0.1-1-el6.src.rpm exfat-utils-1.0.1-1.el6.src.rpm
```

在主目录下，会出现rpmbuild目录：

```cpp
cd ~/rpmbuild/SPECS
rpmbuild -ba fuse-exfat.spec
rpmbuild -ba exfat-utils.spec
```

构建完成后, 即可在 `~/rpmbuild/RPMS` 里面找到生成的 `RPM`( 根据系统架构, 分别在 `x86_64` 或 `i386` 目录下, 其中名字中带有 `debuginfo` 的包不必安装):


```cpp
cd ~/rpmbuild/RPMS/x86_64
sudo rpm -ivh fuse-exfat-1.0.1-1.el7.x86_64.rpm
sudo rpm -ivh exfat-utils-1.0.1-1.el7.x86_64.rpm
```

这样就安装完成了。


##2.2	挂载exfat
-------

可以通过以下命令来挂载exfat的U盘了：

```cpp
sudo mount.exfat /dev/sdc1 /mnt
OR
sudo mount /dev/sdc1 /mnt
```




#3	支持挂载exFAT文件系统
-------


`RPM` 源中NTFS文件系统的支持是由 `ntfs-3g` 软件包来完成的



##3.1	安装ntfs-3g模块
-------

###3.1.1	使用yum的安装方法：
-------


请确定你已经安装了 `rpmforge` 软件库的源. 

请参考：RHEL/CentOS 5.5使用第三方软件库


然后安装下列组件

```cpp
yum install fuse ntfs-3g -y
```

`nfts-3g` 并不再标准的源中, 如果提示未找到软件包, 请先添加 `EPEL` 源, 参见[CentOS7/RHEL7安装EPEL扩展仓库步骤详解](http://blog.csdn.net/gatieme/article/details/70232358)

注：如果你在使用 CentOS 5.3 或更旧版本, 那么你需要安装来自 `ELRepo` 的` mod-fuse`



###3.1.2	使用ntfs-3g官方源码编译安装
-------


目前 `2017-04-19`, `ntfs-3g` 的最新版本是 `2017-03-23`


官网 : http://www.tuxera.com/community/open-source-ntfs-3g/

`ntfs-3g`下载页面 : https://tuxera.com/opensource/ntfs-3g_ntfsprogs-2017.3.23.tgz

安装步骤 :

```cpp
wget https://tuxera.com/opensource/ntfs-3g_ntfsprogs-2017.3.23.tgz
tar zxvf ntfs-3g_ntfsprogs-2017.3.23.tgz
cdntfs-3g_ntfsprogs-2017.3.23
./configure
make
make install
```


`yum` 只适用于 `Redhat` 系, 编译安装适用于所有 `Linux` 发行版


##3.2	挂载NTFS文件系统
-------

假设你的 `NTFS` 文件系统是 `/dev/sdb1` 而你将会把它挂载在 `/mnt/windows/c`, 请执行以下步骤.

*	创建挂载点。（一般建议挂在mnt目录里）

```cpp
mkdir /mnt/windows/c
```

*	挂载NTFS分区：

```cpp
mount -t ntfs-3g /dev/sdb1 /mnt/windows/c
OR
mount /dev/sdb1 /mnt/windows/c
```

>注 : 这里的 `sdb1` 是指 `SATA` 或 `SCSI` 硬盘的第一个分区, 如果是老式的 `IDE` 硬盘, 会是`hda1`, 具体请用 `fdisk -l` 查看.


<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作.
