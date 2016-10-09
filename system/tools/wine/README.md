Ubuntu安装wine和Wine QQ
=======


| CSDN | GitHub |
|:----:|:------:|
| [Ubuntu安装wine和Wine QQ(2012国际版)](http://blog.csdn.net/gatieme/article/details/52770494#t4) | [`AderXCoding/system/tools/wine`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/wine) |

<br>
>  参照
>
>[Wine--Ubuntu Wiki](http://wiki.ubuntu.org.cn/Wine)
>
>[QQ--Ubuntu Wiki](http://wiki.ubuntu.org.cn/QQ)



#1	安装wine
-------

##1.1	安装源中的wine
-------

```cpp
sudo apt-get install wine
```
因为版本比较旧，所以通常不用，改用PPA中的wine。

##1.2	安装最新版 wine
-------

参见 https://wiki.winehq.org/Ubuntu

ubuntu 官方自带了 wine ，但是推荐用 winehq 官方提供的最新版本 wine ，新版本解决了很多以前显得麻烦的问题。

> PPA地址：
>
>https://launchpad.net/~wine/+archive/ubuntu/wine-builds

```cpp
sudo dpkg --add-architecture i386 

sudo add-apt-repository ppa:wine/wine-builds
sudo apt-get update
sudo apt-get install wine-devel
```

要注意，若安装wine包是老的稳定版, 新开发版本是`wine-devel`, 经常有不少优化和修正。

如果愿意安装比`devel`稍微更 devel 的 staging 版本的话，可以试试wine-staging


![wine的版本信息](wine-version.png)


#1.3	配置
-------

```cpp
winecfg
```

然后配置完成即可


#2	安装wine QQ 2012 国际版
-------


有几个备选方案

| 方案 | 描述 |
|:---:|:----:|
| UKylin Wine QQ | Ubuntu Kylin麒麟团队做出的wine QQ安装包|
| longene-wine-qq | [longene](http://www.longene.org/)团队推出的QQ安装包, Longene是一个自由、开源的操作系统项目,致力于在Linux上兼容Windows应用 |
| 自己制作wine QQ | 自己通过最原始的方法, 制作wine QQ |


>参见
>
> http://blog.csdn.net/gatieme/article/details/44856359#t35



但是我们最终选定了`Ubuntu Kylin`的`WineQQ2012`国际版, 因为最稳定

>下载地址
>
>http://www.ubuntukylin.com/applications/showimg.php?lang=cn&id=23
>
>http://www.ubuntukylin.com/application/show.php?lang=cn&id=279


下载完成后是个`wine-qqintl.zip`的压缩包

```cpp
cd wine-qqintl
```

安装此目录下的所有文件

```cpp
sudo dpkg –i fonts-wqy-microhei_0.2.0-beta-2_all.deb

sudo dpkg –i ttf-wqy-microhei_0.2.0-beta-2_all.deb

sudo dpkg –i wine-qqintl_0.1.3-2_i386.deb
```


如果期间安装出错, 说明有某些依赖库没有安装, 则使用如下命令修复依赖关系

```cpp
sudo apt-get install -f
```

![WineQQ2012](wineqq2012.png)


