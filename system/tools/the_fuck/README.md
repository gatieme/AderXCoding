又是一个名叫草泥马的项目：thefuck--修复错误的命令行扩展
=======

| CSDN | GitHub |
|:----:|:------:|
| [又是一个名叫草泥马的项目：thefuck](http://blog.csdn.net/gatieme/article/details/55804976) | [`AderXCoding/system/tools/the_fuck`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/the_fuck) |


本文转载自  [又是一个名叫草泥马的项目：thefuck](https://segmentfault.com/a/1190000002740344)



<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处
<br>

本文转载自  [又是一个名叫草泥马的项目：thefuck](https://segmentfault.com/a/1190000002740344)

一般而言，能受到广泛关注的开源项目分为这么几类：

| 类别 | 例子 |
|:---:|:---:|
| 分离出去的项目 | 例如 io.js |
| 解决了痛点的项目 | 例如 jQuery |
| 提高效率的项目 | 例如 Anjular.js |
| 大公司的项目或者本来就特别火的项目 | 例如 .NET |

当然也有脑洞大开的项目，比如 SegmentFault 上之前介绍过的[《编程语言中的精品——草泥马语》](http://segmentfault.com/a/1190000000606169)

更比如，今天要讲的主角：[thefuck](https://github.com/nvbn/thefuck)

开发者都或多或少接触过 `linux` 接触过命令行, 当然肯定也都被命令行狠狠地`"fuck"`过. 我很多时候都是微不足道的原因导致了命令行出错, 例如将 `python` 输入成 `ptyhon`, 例如将 `ls -alh` 输入成 `ls a-lh` 而导致出错，这个时候我会想说 : "fuck"

#1	起源
-------


开发 `thefuck` 的这位同仁, 恐怕也经常会有这种不和谐的情况. 因此开发了这个软件 `thefuck`.

`thefuck` 不仅仅能修复字符输入顺序的错误, 在很多别的你想说"fuck"的情况下, `thefuck` 依然有效。

例如以下情况。

#2	案例
-------


任何情况下你想说"我操", 你都可以用得到 `thefuck`

例如：

##2.1	`ls` 和 `sl`
-------


使用过 `ubuntu` 的开发者很多都知道有这么一条命令：`sl`. 这条命令是在你将 `ls` 错误地输成 `sl` 时, 会在屏幕上快速驶过一辆火车. 当然, 有了 `thefuck`, `sl` 似乎也可以退休了。

```cpp
➜ sl
The program 'sl' is currently not installed. You can install it by typing:
sudo apt-get install sl
➜ fuck
ls #修正
a.go    b.php    dockerui    jekyll-casper    main.go    PureBlog
```


##2.2 忘记 sudo
-------

```cpp
➜ apt-get install vim
E: Could not open lock file /var/lib/dpkg/lock - open (13: Permission denied)
E: Unable to lock the administration directory (/var/lib/dpkg/), are you root?

➜ fuck
sudo apt-get install vim
[sudo] password for nvbn:
Reading package lists... Done
```

##2.3  操作 git
-------


```
➜ git push
fatal: The current branch master has no upstream branch.
To push the current branch and set the remote as upstream, use

    git push --set-upstream origin master


➜ fuck
git push --set-upstream origin master
Counting objects: 9, done.
```

##2.4  错输命令
-------


```
➜ puthon
No command 'puthon' found, did you mean:
 Command 'python' from package 'python-minimal' (main)
 Command 'python' from package 'python3' (main)
zsh: command not found: puthon

➜ fuck
python
Python 3.4.2 (default, Oct  8 2014, 13:08:17)
```

##2.5  选项修正
-------


```
➜ git brnch
git: 'brnch' is not a git command. See 'git --help'.

Did you mean this?
    branch

➜ fuck
git branch
* master
```


##2.7  其他
-------


thefuck 还有其他很多种用法，就等着你去发现。

#3  安装
-------


##3.1  安装需求
-------


*	python (2.7+ or 3.3+)

*	pip

*	python-devAderXCoding


##3.2  安装方法
-------


可以使用 pip 安装：sudo pip install thefuck
或者使用 OS X、Ubuntu、Arch 的包管理器安装。
安装后配置bash：
alias fuck='eval $(thefuck $(fc -ln -1)); history -r'
Zsh、Fish 和 PowerShell 的 配置方法见这里。

##3.3  更新
-------

更新到最新的 thefuck 的方法非常简单：

```cpp
sudo pip install thefuck --upgrade
```

#4  其他
-------


##4.1  软件原理
-------

前面说了那么多用法，
那么有人觉得 thefuck 可能只是一个用来
thefuck 进行命令修复的模块名和对应的修复原理如下：

| 模块 | 修复 |
|:---:|:----:|
| brew_unknown_command | 修复 brew 命令，例如将 brew docto 修复为 brew doctor |
| cd_parent | 将 cd.. 修正为 cd .. |
| cd_mkdir | cd 进入不存在的目录时尝试创建目录 |
| cp_omitting_directory | cp 时添加 -a 选项 |
| fix_alt_space | 将所有的的Alt+Space 修正为 Space |
| git_add | 修正没有 git add 的情况 |
| git_checkout | git checkout 不存在的分支之前尝试创建分支 |
| git_no_command | 修正错误的选项，例如 git brnch |
| git_push | 如果 push 失败，尝试将 git push 修正为 git push --set-upstream origin $branch |
| has_exists_script | 为所有的提示不存在的命令尝试添加 ./ 前缀 |
| lein_not_task | 修正 lein，例如 lein rpl |
| mkdir_p | mkdir 时尝试添加 -p 选项 |
| no_command | 修正不存在的命令，例如 vom 修正为 vim |
| man_no_space | 将没有空格的 man 命令添加空格，例如 mandiff 修正为 man diff |
| pacman | arch 系统上，如果使用没有安装的软件，尝试使用 pacman 或者 yaourt 安装 |
| pip_unknown_command | 修正错误的 pip 命令，例如 pip isntall 修正为 pip install |
| python_command | 当前目录试图执行没有 x 权限的 python 程序时，修复为添加 python 前缀 |
| sl_ls | sl 修正为 ls |
| rm_dir | 如果删除文件夹，为 rm 添加 -rf 选项 |
| ssh_known_hosts | 如果远程主机公钥不匹配，尝试将远程主机公钥从 know_hosts 中移除 |
| sudo | 如果提示没有权限，尝试添加 sudo |
| switch_layout | 将键盘布局修正为英语布局 |
| apt_get | 如果不存在命令，尝试使用 apt-get 包管理器安装 |
| brew_install | 修正 brew install 的格式 |
| composer_not_command | 修正 composer 命令 |


##4.2  没有启用的模块
-------

| ls_lah | 为 ls 添加 -alh 选项 |
| rm_root | 为 rm -rf / 添加 --no-preserve-root 选项 |

##4.3  自定义规则
-------


当然，你也可以自定义修正规则：
一个自定义规则的案例：

```cpp
def match(command, settings):
    return ('permission denied' in command.stderr.lower()
            or 'EACCES' in command.stderr)
# 获取 stderr 中的字符串和程序返回值（errno），

# 修正规则（命令前添加 sudo）
def get_new_command(command, settings):
    return 'sudo {}'.format(command.script)

# 以下为可选项
# 默认是否开启
enabled_by_default = True
# 附加命令
def side_effect(command, settings):
    subprocess.call('chmod 777 .', shell=True)
# 优先级，数字越大优先级越低。
priority = 1000
```

##4.3  使用须知
-------

虽然 thefuck 带来了很多便利，不过仍然建议注意这件事情：

thefuck 会给出的修正后的命令，但是默认情况下你看到它们的时候，命令都已经默认执行了。
大部分情况下，thefuck 可能给出的是正确的修正，但是小部分情况下，给出的修正并不是你想要的。
所以建议将 ~/.thefuck/settings.py 中的设置改为 require_confirmation = True，这样可以自己决定是否执行修正后的命令。


#5 其他参考
-------


[热门 Python 应用 The Fuck 是如何工作的](http://python.jobbole.com/82528/)


[开源社区--the_fuck介绍](https://www.oschina.net/p/thefuck)



