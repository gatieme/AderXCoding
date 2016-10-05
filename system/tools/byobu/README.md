安装了一个终端分屏工具 byobu
=======


https://help.ubuntu.com/community/Byobu



```cpp
Where there is a shell，there is a way!
```

系统管理员一般在linux会用screen来管理远程会话，可以保持进程或远程终端操作共享，tmux则是screen更灵活先进，而目前正使用推荐的是Byobu，它则是比tmux更简易的版本，不需要太多配置直接可以使用。

*	**亮点** : 一个标签多窗口切割，动态调整大小，保持会话

*	**缺陷** : 中文编码导致窗口字符显示错乱



#1	起因
-------


以前`linux`下装过一次`tmux`, 快捷键太多，实际用起来也是手忙脚乱, 没用起来.

前几天看同事用`byobu`, 听说相当于是`tmux`的定制版. 



实际用起来也是挺好的, 帮助、分栏、移动栏、开新窗口、设置等等, 这些的功能都与键盘最顶上的F1-F12有关，调整窗口都是与方向键有关，很快就记住啦。



#2	byobu简介
-------




`screen`是`linux`下一个终端里实现多`session`的工具, `byobu`是`ubuntu`下`screen`的一个封装(wrapper)

`Byobu`是对`Screen`的强化, 适用于没有使用`GUI`的同学, `Byobu`让`Screen`更加强大, 界面更加直观.

使用`Byobu`后`screen`的下面会有两个状态行, 倒数第二行是每个`shell`的名字, 右边是一个菜单的提示; 最后一行从左至右依次是 : `byobu`的`logo`、系统版本、`uptime`、电池电量、`load_average`、`CPU`状态、内存状态、日期时间, 如果`ubuntu`有更新包或者需要重启, 也会有相应的提示. 并且允许自己添加诸如`wifi`状态、硬盘空间、风扇转速、`hostname`、`IP`地址, 邮件提示等功能.


`byobu`其实就是利用`screen`强大的配置功能搞了很多有用的配置项. 它最大的特性一个是`key-binding`, 将新窗口, 窗口切换, 重命名等操作绑定到了F2~F9等键, 另外, F12键可以锁定终端, 输入登陆密码后才解锁. 另一个特性是屏幕底部显示一系列信息(`status`), 有`cpu`, 内存, 时间等信息.


默认的快捷键主要有 :


>http://byobu.co/documentation.html


| 快捷键 | 描述 |
|:-----:|:---:|
| F2 | new window |
| F3/F4 | switch |
| F5 | reload |
| F6 | Detach |
| F7 | 回滚模式 |
| F8 | rename |
| F12 | lockscreen |
| F2 | Create a new window |
| F3 | Move to previous window |
| F4 | Move to next window |
| F5 | Reload profile |
| F6 | Detach from this session |
| F7 | Enter copy/scrollback mode |
| F8 | Re-title a window |
| F9 | Configuration Menu |
| F12 | Lock this terminal |
| shift-F2 | Split the screen horizontally |
| ctrl-F2 | Split the screen vertically |
| shift-F3 | Shift the focus to the previous split region |
| shift-F4 | Shift the focus to the next split region |
| shift-F5 | Join all splits |
| ctrl-F6 | Remove this split |
| ctrl-F5 | Reconnect GPG and SSH sockets |
| shift-F6 | Detach, but do not logout |
| alt-pgup | Enter scrollback mode |
| alt-pgdn | Enter scrollback mode |
| Ctrl-a $ | show detailed status |
| Ctrl-a R | Reload profile |
| Ctrl-a ! | Toggle key bindings on and off
| Ctrl-a k | Kill the current window |
| Ctrl-a ~ | Save the current window's scrollback buffer |

如果你用的是`putty`, 它默认的按键绑定跟`byobu`的冲突. 在`putty`的`Terminal => Keyboard`配置里选 `"Xterm R6"`后保存, 上面的快捷键就都可以用了



#3	安装与配置
-------

```cpp
sudo apt-get install screen byobu
```


它默认的配置最底部左边是发行版信息, 右边是cpu等信息, 倒数第2行左边是窗口列表, 右边是登陆信息. 觉得它下边占了两行太浪费了, 我希望只占一行, 左边是窗口列表, 右边是 cpu等信息. 所以需要改它的`profile`文件:

```cpp
sudo vi ~/.byobu/profile
```

在这个文件最后找到`hardstatus`和`caption`开头的那两行, 注释掉, 然后加入两行 :

```cpp
hardstatus ignore
caption always '%12`%?%-Lw%50L>%?%{=r}%n*%f %t%?(%u)%?%{-}%12`%?%+Lw%?%11` %= %130`%135`%102`%101`%129`%131`%127`%114`%115`%108`%134`%128`%125`%126`%113`%119`%133`%117`%116`%106`%104`%103`%105`%107`%136`%123`%132`%120`%121`'
```


同目录下还有个`status`文件, 定义了哪些信息需要在右下角显示.

编辑完后按 F5 刷新配置文件, 显示如下图:

使用过程中还发现点问题. 你用`byobu -S yc`新建一个 `session`, 用完后按`F6 detach`, 然后恢复的时候不能象`screen`那样用`-r`参数恢复. 查了下, 原来`byobu`使用了它自己默认的`-S byobu`

所以需要对`byobu`脚本做点修改 :

```cpp
sudo vi `which byobu`
```

找到`NAME="-S $PKG"`那行(79行左右), 在下面加入一句:


```cpp
[ "$#" = "2" ] && [ "$1" = "-r" ] && NAME=
```

意思是当指定了`-r`参数时不用`byobu`它自己的名字. 这样就可以用`-r`来恢复`session`了






















[`iterm2`有些快捷键不能被`byobu`捕获](http://stackoverflow.com/questions/26180096/os-x-byobu-vertical-split)

[不能在 iterm2 + ipython 中 ^←（ctrl + 方向键左）跳过一个单词的童鞋，看这里](http://stackoverflow.com/questions/6205157/iterm2-how-to-get-jump-to-beginning-end-of-line-in-bash-shell)