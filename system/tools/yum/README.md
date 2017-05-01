RHEL/CentOS/Fedora各种源(EPEL、Remi、RPMForge、RPMFusion)配置
=======



| CSDN | GitHub |
|:----:|:------:|
| [RHEL/CentOS/Fedora各种源(EPEL、Remi、RPMForge、RPMFusion)配置](http://blog.csdn.net/gatieme/article/details/71056309) | [`AderXCoding/system/tools/yum`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/yum) |



<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>

本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作

<br>


本文地址：http://blog.csdn.net/gatieme/article/details/71056309







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







#2	Remi源
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
yum localinstall --nogpgcheckhttp://repository.it4i.cz/mirrors/repoforge/redhat/el7/en/x86_64/rpmforge/RPMS/rpmforge-release-0.5.3-1.el7.rf.x86_64.rpm
```



或者



```cpp
rpm -ivh http://repository.it4i.cz/mirrors/repoforge/redhat/el7/en/x86_64/rpmforge/RPMS/rpmforge-release-0.5.3-1.el7.rf.x86_64.rpm
```



或者



```cpp
wget http://repository.it4i.cz/mirrors/repoforge/redhat/el7/en/x86_64/rpmforge/RPMS/rpmforge-release-0.5.3-1.el7.rf.x86_64.rpm

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





##5.1	安装yum-priorities`插件
-------



如果您需要使用以上源, 您需要安装 `yum-priorities`插件



```cpp
yum install yum-plugin-priorities
```





安装完后查看配置信息

```cpp
vim /etc/yum/pluginconf.d/priorities.conf
enabled = 1（可用）/0（不可用）
```





##5.2	设置源的优先级
-------



安装 `yum-priorities` 插件后, 您可以给各个源设置优先级`priority`.



一般设置官方标准源优先级为 `1`, 最高, 第三方推荐 `>10`



编辑 /etc/yum.repos.d/目录下的*.repo 文件来设置优先级。



参数为：





```cpp
priority=N   # N的值为1-99
```

数字越低优先级越高，数字越大优先级越低，安装包选择优先级高的开始安装。







推荐的设置为：



```cpp
[base], [addons], [updates], [extras] … priority=1 

[centosplus],[contrib] … priority=2

Third Party Repos such as rpmforge … priority=N   (where N is > 10 and based on your preference)
```



##5.3	解决冲突
-------





特殊情况 : 但在不同优先级的源中都含有同一个包时, 它的行为可能就不是我们所需要的.

例如, 在 `base` 源中有个包 : `abc-2.2.0.x86_64.rpm`, `base` 是最高优先级. 在其他的优先级中也有许多 `abc` 包, 如果你想安装 `abc-2.1.0-x86_64.rpm`, 通过命令



```cpp
yum install abc-2.1.0
```



就会出现下面的提示

    xx packages excluded due to repository priority protections



并且找不到所需要的包，这是因为在高优先级源中存在的包，会将其他低优先级中的包屏蔽掉，因此无法从低优先级的源中安装所需要的包。

修改priorities的配置文件是/etc/yum/pluginconf.d/priorities.conf

其内容为:



```cpp
[main]

enabled=0   # 0禁用 1启用
```

默认是1;设置enabled = 0, 这样就可以禁用priorities插>件。从而能够安装任意源上的包。







#6	参考资料
-------




[RHEL/CentOS/Fedora各种源(EPEL、Remi、RPMForge、RPMFusion)配置](http://www.cnblogs.com/mawanglin2008/p/3532247.html)



[yum源的优先级](http://461205160.blog.51cto.com/274918/1727419)


[修改centos 7.0 的yum源优先级priority](http://blog.csdn.net/dear_mywork/article/details/53869615)





<br>



<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作.

