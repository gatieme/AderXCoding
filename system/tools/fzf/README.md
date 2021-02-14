---

title: 使用模糊搜索神器 FZF 来提升办公效率
date: 2021-02-15 00:32
author: gatieme
tags: linux
categories:
        - linux
        - debug
thumbnail:
blogexcerpt: FZF 是目前最快的模糊搜索工具. 使用golang编写. 结合其他工具(比如 ag 和 fasd)可以完成非常多的工作. 前段时间, 有同事给鄙人推荐了 FZF, 通过简单的配置, 配合 VIM/GIT 等工具食用, 简直事半功倍, 效率指数级提升, 因此推荐给大家.

---


| 日期 | 作者 | GitHub| CSDN | BLOG |
| ------- |:-------:|:-------:|:-------:|:-------:|
| 2021-02-15 | [成坚-gatieme](https://kernel.blog.csdn.net) | [`AderXCoding/system/tools/fzf`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/fzf) | [使用模糊搜索神器 FZF 来提升办公体验](https://blog.csdn.net/gatieme/article/details/113828826) | [Using FZF to Improve Productivit](https://oskernellab.com/2021/02/15/2021/0215-0001-Using_FZF_to_Improve_Productivity)|


<br>



# 1 fzf 介绍
-------


[fzf](https://github.com/junegunn/fzf) 是一款使用 GO 语言编写的交互式的命令行工具, 可以用来查找任何 列表内容、文件、历史命令、 本机绑定的host、 进程、 Git 分支、进程 等.

我们可以通过 FZF 结合 git 等工具来提升我们的办公体验.

[github 仓库地址](https://github.com/junegunn/fzf)

https://github.com/junegunn/fzf

# 2 fzf 安装
-------


FZF 目前已经在各大发行版的源中集成了, 比如 ubuntu 19.10 之后, 可以直接使用 apt 进行安装

| Package Manager | Linux Distribution      | Command                            |
| ---             | ---                     | ---                                |
| APK             | Alpine Linux            | `sudo apk add fzf`                 |
| APT             | Debian 9+/Ubuntu 19.10+ | `sudo apt-get install fzf`         |
| Conda           |                         | `conda install -c conda-forge fzf` |
| DNF             | Fedora                  | `sudo dnf install fzf`             |
| Nix             | NixOS, etc.             | `nix-env -iA nixpkgs.fzf`          |
| Pacman          | Arch Linux              | `sudo pacman -S fzf`               |
| pkg             | FreeBSD                 | `pkg install fzf`                  |
| pkg_add         | OpenBSD                 | `pkg_add fzf`                      |
| XBPS            | Void Linux              | `sudo xbps-install -S fzf`         |
| Zypper          | openSUSE                | `sudo zypper install fzf`          |

当然也可以使用 git clone 的方式安装

```cpp
git clone --depth 1 https://github.com/junegunn/fzf.git ~/.fzf
~/.fzf/install
```

关于更详细的安装方法可以参照 [Installation](https://github.com/junegunn/fzf#installation)

# 3 fzf 使用
-------


## 3.1 FZF 基本使用
-------

fzf 默认会启用用户交互查找, 从标准输入流(STDIN)读取, 并将匹配内容输出到标准输出流(STDOUT)中:

```cpp
find * -type f | fzf
```

fzf 如果没有接受标准输入流, 那么就会直接进行文件查找(不包含隐藏文件), 可以通过设置 `FZF_DEFAULT_COMMAND` 修改该默认动作: 

## 3.2 FZF 基本操作
-------

```cpp
fzf # 直接输入 fzf, 打开文件搜索功能
```

> 注: 在 fzf 的用户交互界面中, 用户的操作有如下动作可选: 

*   使用CTRL-J/CTRL-K(或者CTRL-N/CTRL-P)进行上下选择
*   使用Enter选中条目, CTRL-C/CTRTRL-G/ESC进行退出操作
*   在多选择模式(-m), 使用TAB和Shift-TAB标记多个条目
*   Emacs 风格按键绑定
*   支持鼠标操作

## 3.3 搜索
-------


### 3.3.1 搜索语法
-------

fzf 默认会以 "extened-search" 模式启动, 这种模式下不支持正则搜索, 但是你可以输入多个搜索关键词, 以空格分隔, fzf 会无序查找匹配所有字符串.

如 ^music .mp3$, sbtrkt !fire.

fzf 提供了一些增强功能的搜索语法, 如下表所示: 


| 标记 | 匹配类型  |  描述 |
| ---     | ---              | ---                              |
| sbtrkt  | 模糊匹配            | 内容匹配sbtrkt(字符匹配)          |
| 'wild   | 精确匹配(单引号)     | 内容包含单词wild(单词匹配)         |
| ^music  | 前缀精确匹配         | 以music开头                       |
| .mp3$   | 后缀精确匹配         | 以.mp3结尾                        |
| !fire   | 反转匹配             | 内容不包含fire                    |
| !^music | 前缀反转匹配         | 不以music开头                      |
| !.mp3$  | 后缀反转匹配         | 不以.mp3结尾                       |

> 注: 如果不想使用模糊匹配或者不想"引用"每个文字, 可以使用 `-e/--exact` 选项. 注意如果使用 `-e/--exact`, 那么 `'` 就变成了解引用, 即:'abc表示匹配a,b和c(a,b,c有序), 而不仅仅是匹配abc.
 

### 3.3.2 或操作
-------


fzf 以空格分隔, 默认使用的是 与 操作(无序), 如果想使用 或 操作, 那么可以使用 `|` : 

```cpp
^core go$ | rb$ | py$ # 表示以`core`开头, 且以`go`或`rb`或`py`结尾
```

>注: | 前后必须带空格. 

### 3.3.3 模糊补全
-------

在 bash 或 zsh 终端上, 可以通过输入 `**` 来触发 fzf 对文件/目录的模糊补全(查找), 如下例子所示:

```cpp
# Files under current directory
# - You can select multiple items with TAB key
vim **<TAB>
```

* 进程 ID 模糊补全

在使用kill命令时, fzf 会自动触发其自动补全功能: 


```cpp
# Can select multiple processes with <TAB> or <Shift-TAB> keys
kill -9 <TAB>
```

* 主机名补全

如下例子所示: 

```cpp
ssh **<TAB>
telnet **<TAB>
```

* 自定义模糊补全

在 bash 上, fzf 的模糊补全功能只对一些预定义的命令集有效(具体命令集: `complete | grep _fzf`), 但是我们也可以为其他命令设置 fzf 模糊补全功能, 如下所示: 

```cpp
# 为 rg 增加模糊补全, rg -F "def main(" **<TAB>
complete -F _fzf_path_completion -o default -o bashdefault rg

# 为 tree 增加模糊补全, tree  **<TAB>
complete -F _fzf_dir_completion -o default -o bashdefault tree
```

fzf 目前有提供相关 API 供我们自定义模糊补全功能, 具体步骤如下: 
1) 首先自定义一个函数, 使用 fzf 提供的 API: `_fzf_complete` 提供补全功能: 

```cpp
# Custom fuzzy completion for "doge" command
#   e.g. doge **<TAB>
_fzf_complete_doge() {
  _fzf_complete "--multi --reverse" "$@" < <(
    echo very
    echo wow
    echo such
    echo doge
  )
}
```

2) 在 bash 中, 使用complete指令链接我们的自定义函数: 

```cpp
[ -n "$BASH" ] && complete -F _fzf_complete_doge -o default -o bashdefault doge
```

3) 终端输入: `doge **<TAB>`, 即可验证结果

## 3.4 按键绑定
-------

fzf 的安装脚本会为 bash, zsh 和 fish 终端设置以下按键绑定: 

| 按键 | 描述 |
| ---     | ---                            |
| CTRL-T  | 命令行打印选中内容                |
| CTRL-R  | 命令行历史记录搜索, 并打印输出      |
| ALT-C   | 模糊搜索目录, 并进入(cd)          |


## 3.5 环境变量
-------


| name                 | description example                                                     |
| ---                  | ---                                                                     |
| FZF_DEFAULT_COMMAND  | 输入为 tty 时的默认命令  export FZF_DEFAULT_COMMAND='fd --type f'          |
| FZF_DEFAULT_OPTS     | 设置默认选项  export FZF_DEFAULT_OPTS="--layout=reverse --inline-info"    |
| FZF_CTRL_T_COMMAND   | 按键映射<CTRL-T>行为设置                                                   |
| FZF_CTRL_T_OPTS      | 按键映射<CTRL-T>选项设置                                                   |
| FZF_CTRL_R_OPTS      | 按键映射<CTRL-R>选项设置                                                   |
| FZF_ALT_C_COMMAND    | 按键映射<CTRL-C>行为设置                                                   |
| FZF_ALT_C_OPTS       | 按键映射<CTRL-C>选项设置                                                   |


fzf 默认会以全屏方式显示交互界面, 可以使用--height选项设置交互界面高度: 

```cpp
vim $(fzf --height 40%)
```

可以通过设置$FZF_DEFAULT_OPTS变量更改 fzf 默认行为: 

```cpp
# 设置 fzf 默认交互界面大小
export FZF_DEFAULT_OPTS='--height 40%' 
```


## 3.6 预览窗口
-------

可以通过提供 `--preview` 选项打开预览窗口, 并设置响应命令输出到预览窗口上.


```cpp
# {} is replaced to the single-quoted string of the focused line
fzf --preview 'cat {}' # 预览文件内容
fzf --preview 'rg -F "def main(" -C 3 {}' # 预览 Python 文件 main 函数前后3行代码
```


## 3.7 高级配置
-------

### 3.7.1 更改查找引擎
-------

默认情况下, fzf 使用的查找引擎是系统自带的 `find` 命令, 这里我们可以对其进行更改, 换成更高效的查找引擎. 

```cpp
# 使用 rg 进行搜索
export FZF_DEFAULT_COMMAND='rg --files --hidden'
```

### 3.7.2 自定义命令
-------

我们可以通过设置按键映射在 fzf 交互界面直接开启外部进程 (`execute, execute-silent`) 运行我们选中的文件

* 通过快捷键执行外部程序

```cpp
# 在交互界面选中文件后, 按下 F1, 直接使用 vim 打开
fzf --bind 'f1:execute(vim {})' 
```

* 简化命令

可以通过定义 shell 脚本简化 fzf 命令执行. 比如, 下面示例定义了一个函数, 结合ag实现传参进行模糊搜索, 并用 vim 打开:

```cpp
# fuzzy grep open via ag
vg() {
  local file

  file="$(ag --nobreak --noheading $@ | fzf -0 -1 | awk -F: '{print $1}')"

  if [[ -n $file ]]
  then
     vim $file
  fi
}
```

* 自定义全局快捷键触发

像 fzf 其实已经有为我们提供了一些按键映射, 比如<CTRL-T>, 可以打印出选中文件. 现在我们也仿照写一个该功能脚本, 全局快捷键设为<CTRL-G><CTRL-O>:

1) 首先先写目录搜索(fzf)并打印输出功能脚本: 

```cpp
# .bashrc
outputDir() {
    local dir
    dir=$(find ${1:-.} -type d 2> /dev/null | fzf +m)
    echo $dir
}
```

2)然后进行全局按键映射: 

```cpp
# .bashrc
bind '"\er": redraw-current-line'
bind '"\C-g\C-o": "$(outputDir)\e\C-e\er"'
```

> 注: 
> 1) \e\C-e: shell-expand-line默认按键绑定, 这是最容易的方式进行按键绑定, 缺点就是它对于别名(alias)也会同样进行展开. 
> 2) redraw-current-line: 在非 tmux 终端上, 该选项必须存在, 否则无法清除提示. 
> 3) 先source .bashrc, 然后按快捷键: <CTRL-G><CTRL-O>, 运行结果如下: 

### 3.7.3 为预览窗口增加语法高亮:
-------

预览窗口支持 ANSI 颜色, 因此我们可以为文件内容增加语法高亮. 我们借助 bat 这个库来为我们的文本显示语法高亮功能: 


> 建议安装bat， 是一个Rust编写的独立程序
> 也可以安装rougify(先安装ruby, 然后gem intall rouge)

1) 首先, 安装 bat 库. 具体步骤请查看文档. 
2) 终端输入以下内容: 

```cpp
fzf --preview '[[ $(file --mime {}) =~ binary ]] &&
                 echo {} is a binary file ||
                 (bat --style=numbers --color=always {} ||
                  highlight -O ansi -l {} ||
                  coderay {} ||
                  rougify {} ||
                  cat {}) 2> /dev/null | head -500'
```

结果如下: 


# 4 用 FZF 提升其他工具的效率
-------

## 4.1 Git 的好帮手
-------

```cpp
#---------------------
# modify by gatieme at 2021-02-01 20:47 for FZF
#---------------------
#export FZF_CTRL_T_OPTS="--layout=reserve --preview '(highlight -O ansi -l {} 2> /dev/null || cat {} || tree -C {}) 2> /dev/null | head -200'"
#export FZF_DEFAULT_OPTS="--height 99% -e --layout=reverse --preview '(highlight -O ansi -l {}' --color 'fg:#bbccdd,fg+:#ddeeff,bg:#334455,preview-bg:#223344,border:#778899'"
export FZF_DEFAULT_OPTS="--height 99% -e --layout=reverse --preview '(bat --style=numbers --color=always {} ||  highlight -O ansi -l {} || coderay {} || rougify {} || cat {}) 2> /dev/null '  --color 'fg:#bbccdd,fg+:#ddeeff,bg:#334455,preview-bg:#223344,border:#778899'"


function fview()
{
  fzf -e --layout=reserve --preview="~/.file_view.sh {$2} $1"
}

function lsf()
{
  ls $1 | fview $1
}

function cdf()
{
  cd $(fdfind --type directory | fzf)
}

function gitlog()
{
  git log --oneline $* | fzf -e --multi --preview="git show {+1}"
}

function gitblame()
{
  git blame $1 | fzf -e --layout=reverse --preview="git show {1}" $2
}

function gitcheckout()
{
  git checkout $(git branch -a) | fzf --preview="git log --oneline {1}"
}
```


当然大家可以使用别的大神已经集成好的配置 [wfxr/forgit](https://github.com/wfxr/forgit)


## 4.2 VIM 大杀器
-------


fzf 本身并不是一个vim 插件, 本来作者只提供了基本的wrapper函数(比如fzf#run). 但后来作者发现很多人并不熟悉 VIMScript, 所以就创建一个默认的 [vim plugin](https://github.com/junegunn/fzf.vim).

如果对FZF和vim和结合感兴趣可以看： [VIM与模糊搜索神器FZF的集成用法 - 从简单到高级](https://segmentfault.com/a/1190000016186540)



# 5 参考资料
-------


## 5.1 中文资料
-------

由于开始对于 FZF 不甚了解, 因此本博文较多参考了 [fzf - 命令行模糊搜索神器](https://www.jianshu.com/p/b48131e4ad06) 和 [模糊搜索神器fzf](https://segmentfault.com/a/1190000011328080). 在这里对这两位作者的成果表示尊重和感谢. 鄙人同一时间正在写其他技术博文, 为了保证其他博文的细致, 因此这篇略显粗糙, 敬请谅解.

[FZF wiki](https://github.com/junegunn/fzf/wiki)

[模糊搜索神器FZF番外篇](https://segmentfault.com/a/1190000016186043)


## 5.2 外文资料
-------

[Improving Vim Workflow With fzf](https://pragmaticpineapple.com/improving-vim-workflow-with-fzf/)

[Using FZF to Improve Productivity](https://medium.com/akatsuki-taiwan-technology/using-fzf-to-improve-productivity-84da1df28163)

[Boost Your Command-Line Productivity With Fuzzy Finder](https://medium.com/better-programming/boost-your-command-line-productivity-with-fuzzy-finder-985aa162ba5d)

[Why you should be using fzf, the command line fuzzy finder](https://www.freecodecamp.org/news/fzf-a-command-line-fuzzy-finder-missing-demo-a7de312403ff)

[Improve Your Workflow in the Terminal with These fzf Tips](https://revelry.co/resources/development/terminal-workflow-fzf)

本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>

因本人技术水平和知识面有限, 内容如有纰漏或者需要修正的地方, 欢迎大家指正, 鄙人在此谢谢啦

**转载请务必注明出处, 谢谢, 不胜感激**

<br>




<br>

*   本作品/博文 ( [AderStep-紫夜阑珊-青伶巷草 Copyright ©2013-2017](http://blog.csdn.net/gatieme) ), 由 [成坚(gatieme)](http://blog.csdn.net/gatieme) 创作.

*   采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可. 欢迎转载、使用、重新发布, 但务必保留文章署名[成坚gatieme](http://blog.csdn.net/gatieme) ( 包含链接: http://blog.csdn.net/gatieme ), 不得用于商业目的.

*   基于本文修改后的作品务必以相同的许可发布. 如有任何疑问, 请与我联系.

*   **转载请务必注明出处, 谢谢, 不胜感激**
<br>
