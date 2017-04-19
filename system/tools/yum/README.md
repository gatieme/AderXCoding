RHEL/CentOS/Fedora各种源(EPEL、Remi、RPMForge、RPMFusion)配置
=======

| CSDN | GitHub |
|:----:|:------:|
| [You-Get--基于Python3的开源网络视频下载工具](http://blog.csdn.net/gatieme/article/details/61623891) | [`AderXCoding/system/tools/you-get`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/you-get) |

<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作
<br>

[RHEL/CentOS/Fedora各种源(EPEL、Remi、RPMForge、RPMFusion)配置](http://www.cnblogs.com/mawanglin2008/p/3532247.html)



`CentOS` 默认自带 `CentOS-Base.repo` 源, 但官方源中去除了很多有版权争议的软件, 而且安装的软件也不是最新的稳定版.

`Fedora` 自带的源中也找不到很多多媒体软件, 如果需要安装, 必需先添加其他源, 如 `RPMFusion` 和 `RPMForge` 等第三方软件库.

下面我们介绍各种第三方软件库, 以下软件库适用于与 `RHEL` 完全兼容的 `linux` 发行版, 如 `CentOS`, `Fedora`, `Scientific Linux`. `Scientific Linux` 大家可能有点陌生, 它与 `CentOS` 类似, 是 `RedHat Linux` 的克隆版.



#1	EPEL源
-------

`EPEL`, 即 `Extra Packages for Enterprise Linux`, 是由 `Fedora` 社区创建维护, 为 `RHEL` 及衍生发行版如 `CentOS`、`Scientific Linux` 等提供高质量软件包的项目.


`EPEL`中含有大量的软件, 对官方标准源是一个很好的补充。


>"EPEL (Extra Packages for Enterprise Linux  ) is a Fedora Special Interest Group that creates, maintains, and manages a high quality set of additional packages for Enterprise Linux, including, but not limited to, Red Hat Enterprise Linux (RHEL), CentOS and Scientific Linux (SL)."

*	wiki: http://fedoraproject.org/wiki/EPEL

*	Fedora EPEL 下载：http://mirrors.fedoraproject.org/publiclist/EPEL/

*	EPEL 下载地址：http://download.fedora.redhat.com/pub/epel/

请针对不同的版本下载相应的包.

例如 `CentOS7` 添加阿里云的EPEL源

```cpp
yum localinstall --nogpgcheck http://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
```

或者

```cpp
rpm -vih http://dl.fedoraproject.org/pub/epel/7/x86_64/e/epel-release-7-9.noarch.rpm
```

或者

```cpp
wget http://dl.fedoraproject.org/pub/epel/7/x86_64/e/epel-release-7-9.noarch.rpm
rpm -vih epel-release-7-2.noarch.rpm
```



##2	Remi源
-------


`Remi` 源大家或许很少听说， 但是我们强烈推荐, 尤其对于不想编译最新版的 `linux` 使用者, 因为 `Remi` 源中的软件几乎都是最新稳定版.

或许您会怀疑稳定不?

放心吧, 这些都是 `Linux` 骨灰级的玩家编译好放进源里的, 他们对于系统环境和软件编译参数的熟悉程度毋庸置疑.


Remi下载地址 : http://rpms.famillecollet.com/

您也需要针对不同的版本号下载.

例如 `CentOS 7`添加官方的 `Remi` 源

```cpp
yum localinstall --nogpgcheck http://rpms.famillecollet.com/enterprise/remi-release-7.rpm
```

或者

```cpp
rpm -ivh http://rpms.famillecollet.com/enterprise/remi-release-7.rpm
```

或者

```cpp
wget http://rpms.famillecollet.com/enterprise/remi-release-7.rpm
rpm -ivh remi-release-7.rp
```

#3	RPMForge源
-------

`RPMForge` 是 `CentOS` 系统下的软件仓库， 拥有 `4000` 多种的软件包, 被 `CentOS` 社区认为是最安全也是最稳定的一个软件仓库.

RPMForge官方网站 : http://repoforge.org/
Github : https://github.com/repoforge
RPMForge下载地址 http://repository.it4i.cz/mirrors/repoforge/redhat/el7/en/x86_64/rpmforge/RPMS/

例如CentOS6.5添加官方的RPMForge源

```cpp
yum localinstall --nogpgcheck http://repository.it4i.cz/mirrors/repoforge/redhat/el7/en/x86_64/rpmforge/RPMS/rpmforge-release-0.5.3-1.el7.rf.x86_64.rpm
```


CentOS 7.0添加官方的RPMForge源

```cpp
yum localinstall --nogpgcheck http://pkgs.repoforge.org/rpmforge-release/rpmforge-release-0.5.3-1.el7.rf.x86_64.rpm
```

或者

```cpp
rpm -ivh http://pkgs.repoforge.org/rpmforge-release/rpmforge-release-0.5.3-1.el7.rf.x86_64.rpm
```

或者

```cpp
wget http://pkgs.repoforge.org/rpmforge-release/rpmforge-release-0.5.3-1.el7.rf.x86_64.rpm
rpm -ivh rpmforge-release-0.5.3-1.el7.rf.x86_64.rpm
```


#4	RPMFusion源
-------

如果您现在正在使用`Fedora 15`， 对 `RPMFusion`一定不陌生吧， 各种音频软件如 `MPlayer` 在标准源中是没有的， 一般先安装 `RPMFusion`源, 之后就可以放便地 `yum install` 各种需要的软件啦。

`CentOS` 官方说 `RPMFusion` 软件库里面的软件稳定性不如`rpmforge`

`RPMFusion` 官网 : http://rpmfusion.org/

包下载 http://download1.rpmfusion.org

包括两个包, `free` 和 `non_free`

>注意 : 在安装 `RPMFusion`源之前需要先安装 `epel-release`


```cpp
#FREE
yum localinstall http://download1.rpmfusion.org/free/el/rpmfusion-free-release-7.noarch.rpm

#NON_FREE
yum localinstall http://download1.rpmfusion.org/nonfree/el/rpmfusion-nonfree-release-7.noarch.rpm


```

或者

```cpp
#FREE
rpm -ivh http://download1.rpmfusion.org/free/el/rpmfusion-free-release-7.noarch.rpm

#NONFREE
rpm -ivh http://download1.rpmfusion.org/nonfree/el/rpmfusion-nonfree-release-7.noarch.rpm
```

或者

```cpp
#FREE
wget http://download1.rpmfusion.org/free/el/rpmfusion-free-release-7.noarch.rpm
rpm -ivh rpmfusion-free-release-7.noarch.rpm

#NON_FREE
wget http://download1.rpmfusion.org/nonfree/el/rpmfusion-nonfree-release-7.noarch.rpm
rpm -ivh rpmfusion-nonfree-release-7.noarch.rpm
```


其他版本请详见 : http://rpmfusion.org/Configuration


#5	为各种源添加优先级别
-------



以上源对 `CentOS` 等系统完全兼容, 但各软件库之间并不能保证完全兼容没有冲突.


如果您需要使用以上源, 您需要安装 `yum-priorities`插件

安装 `yum-priorities` 插件后, 您可以给各个源设置优先级`priority`.

一般设置官方标准源优先级为 `1`, 最高, 第三方推荐 `>10`


```cpp
priority=N （N为1到99的正整数，数值越小越优先）

[base], [addons], [updates], [extras] … priority=1
[CentOSplus],[contrib] … priority=2
```

其他第三的软件源为：priority=N （推荐N>10）

##5.2	CentOS-Base.repo
-------

```cpp
[base]

name=CentOS-$releasever - Base

mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=os

#baseurl=http://mirror.centos.org/centos/$releasever/os/$basearch/

gpgcheck=1

gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-6

priority=1
```



##5.3	`remi.repo` 

将`[remi]` 中的 `enabled=0` 改成 `enabled=1` 来启用 `remi` 源

```cpp
rpm –import /etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL-7

rpm –import /etc/pki/rpm-gpg/RPM-GPG-KEY-remi
```


在 `remi.repo` 中和 `epel.repo`中添加 `priority` 设置即可使用.



<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作.
