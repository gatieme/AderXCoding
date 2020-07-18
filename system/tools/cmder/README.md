title: Cmder 中文乱码设置
date: 2020-07-18 21:37
author: gatieme
tags: linux
categories:
        - linux
thumbnail:
blogexcerpt: Cmder 是 Windows 下替换原有 cmd 的绝佳工具, 但是与默认的 cmd 一样, 都与 git 等工具命令行存在一些兼容性问题, 比如中文乱码问题.

---


| 日期 | 作者 | GitHub| CSDN | BLOG |
| ------- |:-------:|:-------:|:-------:|:-------:|
| 2020-07-18 |  [gatieme](https://blog.csdn.net/gatieme) | [AderXCoding](https://github.com/gatieme/AderXCoding/blob/master/system/tools/cmder/README.md) | [Cmder中文乱码设置](https://blog.csdn.net/gatieme/article/details/107433834) |


# 1    问题描述-cmder git 中文乱码
-------



Cmder 是 Windows 下替换原有 cmd 的绝佳工具, 但是与默认的 cmd 一样, 都与 git 等工具命令行存在一些兼容性问题, 比如中文乱码问题.




![0001-cmder 中文乱码](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/cmder/1.png)





# 2    问题分析
-------

中文乱码本质上都是编码配置的问题, 一般都可以通过配置环境变量来解决问题.
cmder 是一个伪 unix 的终端工具, 可以在 win 下为我们提供一个类 Unix 方式的终端工具. 因此我们环境变量的配置应该也是类似的. 尝试一下子

## 2.1 LOCALE 设置
-------



locale这个单词中文翻译成地区或者地域, 其实这个单词包含的意义要宽泛很多。Locale是根据计算机用户所使用的语言, 所在国家或者地区, 以及当地的文化传统所定义的一个软件运行时的语言环境.

![0002-LOCALE 信息](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/cmder/2.png)

那么我们一般设置 LC 等变量的格式为 zh_CN.GB2312, 这到底是在说什么？ 

Locale是软件在运行时的语言环境, 它包括语言(Language), 地域 (Territory) 和字符集(Codeset)。一个locale的书写格式为: 语言[_地域[.字符集]]。所以说呢, locale总是和一定的字符集相联系的
设定locale就是设定12大类的locale分类属性, 即12个LC_*。除了这12个变量可以设定以外, 为了简便起见, 还有两个变量：LC_ALL和LANG。它们之间有一个优先级的关系：LC_ALL > LC_* >LANG。可以这么说, LC_ALL是最上级设定或者强制设定, 而LANG是默认设定值.

另外LANG和LANGUAGE有什么区别呢?

LANG - Specifies the default locale for all unset locale variables
LANGUAGE - Most programs use this for the language of its interface
LANGUAGE是设置应用程序的界面语言。而LANG是优先级很低的一个变量, 它指定所有与locale有关的变量的.




## 2.2 问题修复
-------

通过上面的分析我们知道, 我们只需要设置 LANG 变量为 zh_CN.UTF-8
尝试在终端界面设置下 LANG. 看问题是否得到解决.

```cpp
set LANG=zh_CN.UTF-8
```



可以看到,  cmder 中 git 能正常显示中文了.


![0003-正常显示中文](https://raw.githubusercontent.com/gatieme/AderXCoding/master/system/tools/cmder/3.png)

# 3 问题解决
-------

总不能每次都在终端中设置 LANG 或者 LC_ALL 变量吧. 最便捷的方法是在配置文件中将环境变量固化下来.

或者直接在在 Cmder 安装目录下的 config/user-profile.cmd 配置文件中添加配置信息


这样就可以解决中文乱码的问题.