UBuntu安装新版的 Thunderbird 邮件客户端
=======

| CSDN | GitHub |
|:----:|:------:|
| [Linux下安装新版的 Thunderbird 邮件客户端](http://blog.csdn.net/gatieme/article/details/78174372) | [`AderXCoding/system/tools/thunderbird`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/thunderbird) |

<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>

本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作

因本人技术水平和知识面有限, 内容如有纰漏或者需要修正的地方, 欢迎大家指正, 也欢迎大家提供一些其他好的调试工具以供收录, 鄙人在此谢谢啦

<br>


#1	Thunderbird介绍
-------


`Thunderbird` 是一个开源自由的跨平台的基于 `web` 的电子邮件、新闻和聊天客户端应用程序， 其旨在用于管理多个电子邮件帐户和新闻源。 `Thunderbird` 目前最新的版本是 `52.x`, 下面我们向您演示在 `Linux` 安装最新的 `Thunderbird` 邮件客户端

查看更多关于 Thunderbird  版本的新功能和已知问题在

https://www.mozilla.org/en-US/thunderbird/52.4.0/releasenotes/

#2	安装 `Thunderbird` 邮件客户端
-------

在许多 `Linux` 发行版中， `Thunderbird` 包已经默认包含在内, 并且可以使用默认包管理系统来安装, 这样可以 :

1.	确保你具有所有需要的库

2.	添加桌面快捷方式以启动 Thunderbird

3.	使 Thunderbird 可供计算机上的所有系统用户访问

4.	它可能不会为你提供最新版本的 Thunderbird

要从系统默认仓库中安装 Thunderbird：


```cpp
#	[在基于 Ubuntu 的系统中]
sudo apt-get install thunderbird

#[在基于 Fedora 的系统中]
dnf install thunderbird
```

但是从默认仓库中安装的话将带给你的是旧版本 `Thunderbird`. 如果要安装最新版本的 `Mozilla Thunderbird`, 可以使用 `Mozilla` 团队维护的 `PPA`.

在 `Ubuntu` 及其衍生版中使用 `CTRL + ALT + T` 从桌面打开终端并添加 `Thunderbird` 仓库.

```cpp
sudo add-apt-repository ppa:ubuntu-mozilla-security/ppa
```

接下来，使用 `apt-get update` 命令升级软件包.

```cpp
sudo apt-get update
```

系统升级完成后, 使用下面的命令安装.

```cpp
sudo apt-get install thunderbird
```

就是这样了, 你已经成功在 `Linux` 中安装了 `Thunderbird`. 在 [`Thunderbird` 下载页](https://www.mozilla.org/en-US/thunderbird/all/)中还有用于其他操作系统的软件包。

![安装新版的 `Thunderbird` 邮件客户端](thunderbird.png)

<br>

*	本作品/博文 ( [AderStep-紫夜阑珊-青伶巷草 Copyright ©2013-2017](http://blog.csdn.net/gatieme) ), 由 [成坚(gatieme)](http://blog.csdn.net/gatieme) 创作, 

*	采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可. 欢迎转载、使用、重新发布, 但务必保留文章署名[成坚gatieme](http://blog.csdn.net/gatieme) ( 包含链接: http://blog.csdn.net/gatieme ), 不得用于商业目的, 

*	基于本文修改后的作品务必以相同的许可发布. 如有任何疑问，请与我联系.