Ubuntu中Terminal和GNOME文件管理器的互通方法及命令
=======

| CSDN | GitHub |
|:----:|:------:|
| [Aderstep--紫夜阑珊-青伶巷草](http://blog.csdn.net/gatieme) | [`AderXCoding/system/tools`](https://github.com/gatieme/AderXCoding/tree/master/system/tools) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作.
<br>


`Nautilus` (鹦鹉螺), 是 `GNOME` 桌面环境中默认的文件管理器. 虽然 `Nautilus` 稍显笨重, 但是功能非常全面, 在 `Linux` 中提供标签支持, 你可以通过多个标签来浏览你硬盘中的文件, 支持书签, 并在左边的"位置(`places`)"中列出你的硬盘上的分区(可以通过点击分区后的 三角型的图标卸载)、主文件夹、桌面. 支持回收站里的文件还原, 在浏览方式中支持"紧凑视图"等等.



#1	终端中打开文件管理器
-------

*	`Terminal` -> `GNOME` 文件管理器


`Terminal` 中在制定路径打开 `GNOME` 文件管理器

使用命令

```cpp
gnome-open	url
```

![终端中使用 `gnome-open` 打开目录](gnome-open-url.png)


或者

```cpp
nautilus	url
```

![终端中使用 `nautilus` 打开目录](nautilus-url.png)


#2	文件管理器中添加右键打开终端
-------


*	`GNOME` 文件管理器 -> `Terminal`


`gnome` 文件管理器中添加右键打开终端


需要文件管理器插件 `Nautilus` 的支持, 使用下列命令下载安装 `Nautilus`

```cpp
sudo apt-get install nautilus
sudo apt-get install nautilus-open-terminal
```

安装成功后， 在 `GNOME` 文件管理器的空白处点右键, 弹出菜单中有"在终端中打开"项


这个我们之前就讲解过了, 参见[安装Ubuntu后必须要做的几件事(一)--基础应用篇](http://blog.csdn.net/gatieme/article/details/44856359#t25)

`Nautilus` 的潜力仍可发掘.







<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
<br>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作.
