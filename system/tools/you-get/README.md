You-Get--基于Python3的开源网络视频下载工具
=======

| CSDN | GitHub |
|:----:|:------:|
| [You-Get--基于Python3的开源网络视频下载工具](http://blog.csdn.net/gatieme/article/details/61623891) | [`AderXCoding/system/tools/you-get`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/you-get) |

<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作
<br>



#1  `You-Get` 介绍
-------

`You-Get` 是一个基于 `Python 3` 的下载工具. 使用 `You-Get` 可以很轻松的下载到网络上的视频、图片及音乐

目前 `You-Get` 支持的站点达到了71个, 囊括了国外的 `Youtube`、 `Vimeo` 、 `Tumblr` 、 `Instagram` 等以及国内的爱奇艺、优酷、乐视、哔哩哔哩等.

项目主页 ： https://github.com/soimort/you-get

You-Get主页 ： https://you-get.org/


#2  `You-Get` 安装
-------


安装 `You-Get` 需要安装如下依赖包

*   Python 3
*   FFmpeg (强烈推荐) or Libav
*   (可选) RTMPDump


##2.1  通过pip安装
-------

`you-get` 可从 `PyPI` 镜像中通过 `pip` 包管理器安装. 

```cpp
pip3 install you-get
```

##2.2   使用预装包(仅供Windows)
-------

从https://github.com/soimort/you-get/releases/latest 下载对应版本的二进制包来安装


```cpp
#Windows
wget https://github.com/soimort/you-get/releases/download/v0.4.652/you-get-0.4.652-win32.exe
```

##2.3 通过GitHub下载源码安装
-------

您可选择稳定版 (与PyPI最新版等同) 或 开发版 (更多的热补丁与不稳定功能)的you-get. 解压并将含有you-get的目录加入PATH.

```cpp
#直接下载源码
wget https://github.com/soimort/you-get/archive/master.zip

```

或者, 运行

```cpp
git clone git://github.com/soimort/you-get.git
```

然后编译安装

将目录加入 PATH, 或运行 make install 以安装you-get 于永久路径.


```cpp
make install
```



#3  升级
-------

考虑到 `you-get` 安装方法之差异, 请使 :

```cpp
pip3 install --upgrade you-get
```
或下载最新更新:

```cpp
you-get https://github.com/soimort/you-get/archive/master.zip
```


#4  You-Get 使用
-------


使用方法很简单, 只需要输入

```cpp
you-get 视频--URL
```

据官方介绍, You-Get支持下载[包括Youtube在内的70余家视频网站](https://you-get.org/), 其中还有有丰富技术视频教程的Khan Academy、InfoQ.


`MPV` 使用 `you-get` 在线看视频

```cpp
you-get -p mpv http://www.bilibili.com/video/av3458634/ 
```


下载的视频可以使用 ffmpeg 来合并视频, 参见[使用 `you-get` 或 `youtube-dl` 下载优酷/土豆/爱奇艺高清视频，`FFmpeg` 合并视频](http://blog.csdn.net/abel_qy/article/details/51067964)





#   参考内容
-------

[`You-Get` 中文说明 `Wiki`](https://github.com/soimort/you-get/wiki/中文说明#%E9%80%89%E9%A1%B9-3-%E4%BA%8Egithub%E4%B8%8B%E8%BD%BD)

[使用 `you-get` 或 `youtube-dl` 下载优酷/土豆/爱奇艺高清视频，`FFmpeg` 合并视频](http://blog.csdn.net/abel_qy/article/details/51067964)

[`mpv` + `you-get` 是在线看视频的神器](https://www.v2ex.com/t/246998)

[`You-Get` 官网](https://you-get.org)

[(侵删)转载 <You-Get——基于Python3的媒体下载工具](http://tieba.baidu.com/p/4553147718)

[You-Get——基于Python3的媒体下载工具](http://www.jianshu.com/p/a3f8df948395)

[http://www.codingpy.com/article/using-you-get-to-download-videos/](http://www.codingpy.com/article/using-you-get-to-download-videos/)

[You-Get 一款开源网络视频获取神奇](http://www.bilibili.com/video/av4366369/)


[命令行视频下载工具：You-get 数十个网站都可解析](https://baijiahao.baidu.com/po/feed/share?wfr=spider&for=pc&context=%7B"sourceFrom"%3A"bjh"%2C"nid"%3A"news_4031325661465239968"%7D)



<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作.
