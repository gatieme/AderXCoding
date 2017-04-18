linux下搜狗输入法不能输入中文的解决方案
=======

| CSDN | GitHub |
|:----:|:------:|
| [linux 下搜狗输入法不能输入中文的解决方案](http://blog.csdn.net/gatieme/article/details/68947995) | [`AderXCoding/system/tools/sougoupinyin`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/sougoupinyin) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作
<br>


#1	问题
-------


Ubuntu下一直在使用搜狗拼音, 之前能正常使用, 但是最近几天输入法开始抽风, 无法输出中文.

具体现象是, 可以呼出搜狗输入法界面, 但是候选词列表无显示


如下图所示

![错误](error.jpg)



#2	解决方案
-------


##2.1	删除配置文件，重启搜狗
-------


`ubuntu` 下搜狗的配置文件在 `~/.config` 下


执行如下指令

```cpp
cd ~/.config
find . -name sogou*
find . -name Sogou*
```


将两次搜索到的配置文件删除即可.


一般来说, 总共有如下3个文件夹, 全部删除即可

```cpp
SogouPY、SogouPY.users、sogou-qimpanel
```

删除这3个文件夹，然后重启搜狗.


一般来说上面的方法可以解决了无法输入中文问题, 如果还是不行, 继续下面的尝试


##2.1	重启搜狗输入法
-------


通过下面的命令重启搜狗输入法，看重启后是否可以正常使用：

```cpp
killall fcitx
killall sogou-qinpanel
fcitx
```

##2.2	检查修复安装依赖
-------


因为我之前是可以正常使用的，所以应该不是安装依赖的问题。刚安装好的朋友如果无法使用，可以用下面的命令排除或修复安装依赖问题

```cpp
sudo apt-get install -f
```



#3	参考
-------


[`Linux` 版本无法正常使用的解决方案独立说明](http://pinyin.sogou.com/bbs/forum.php?mod=viewthread&tid=2681098&extra=page%3D1)

[搜狗输入法一夜暴毙？！](http://pinyin.sogou.com/bbs/forum.php?mod=viewthread&tid=2676147&extra=&page=1)


[搜狗 `Linux` 综合区论坛](http://pinyin.sogou.com/bbs/forum.php?mod=forumdisplay&fid=115&page=1)

<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作.
