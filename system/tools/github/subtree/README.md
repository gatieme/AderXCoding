git教程(四)--使用GIT SUBTREE集成项目到子目录
=======

| CSDN | GitHub |
|:----:|:------:|
| [git教程(四)--使用GIT SUBTREE集成项目到子目录](http://blog.csdn.net/gatieme/article/details/64212666) | [`AderXCoding/system/tools/github/subtree`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/github/subtree) |




[Git教程(一)----初识Git](http://blog.csdn.net/gatieme/article/details/43792589)

[git教程(二)--安装和配置git](http://blog.csdn.net/gatieme/article/details/50586476)


[git教程(三)--创建项目并提交更新](http://blog.csdn.net/gatieme/article/details/50595028)


> 本文
>[git教程(四)--使用GIT SUBTREE集成项目到子目录](http://blog.csdn.net/gatieme/article/details/64212666) 
> 转载自
> [使用GIT SUBTREE集成项目到子目录](http://aoxuis.me/post/2013-08-06-git-subtree)






#1  subtree 介绍
-------


##1.1  使用背景
-------

例如, 在项目`Game`中有一个子目录`AI`.

`Game` 和 `AI` 分别是一个独立的 `git` 项目, 可以分开维护. 为了避免直接复制粘贴代码, 我们希望 `Game` 中的 `AI` 子目录与 `AI` 的 `git` 项目关联, 有3层意思：

*   `AI` 子目录使用 `AI` 的 `git` 项目来填充, 内容保持一致. 

*   当 `AI` 的 `git` 项目代码有更新, 可以拉取更新到 `Game` 项目的 `AI` 子目录来. 

*   反过来, 当 `Game` 项目的 `AI` 子目录有变更, 还可以推送这些变更到 `AI` 的 `git` 项目. 


用 `git subtree` 可以轻松满足上面的需求. 


##1.2  subtree对比submodule
-------

如果你没有用过 `git submodule`, 你甚至可以不用了解 `git submodule` 是什么, `submodule` 的基本介绍也不在本文的说明范围内. 虽然它满足了上述差不多的需求, 但是复杂难用, 以至于需要这么长一篇教程才能说清楚用法. 

如果你的项目正在使用 `git submodule`, 你应该知道用 `submodule` 有多么麻烦, 这里还有一篇文章专门解释 [`git submodule` 的缺点](http://codingkilledthecat.wordpress.com/2012/04/28/why-your-company-shouldnt-use-git-submodules/), 可以参考前面教程里的最后一段来删除 `submodule` (是的, 连删除步骤都非常麻烦)

使用 `git subtree` 之后, 管理、更新都更加方便. 

##1.3   什么是`git subtree`
-------


`git subtree` 是一条 `git` 子命令, 本质上 `subtree` 是一种合并策略, 从 `git v1.5.2`, 官方就推荐使用 `subtree` 代替 `submodule`, 所以它并不需要保存. `submodule` 这样的元信息. 

`git subtree` 的前提条件

`subtree` 子命令很晚才集成到 `git` 中, 请确保你的 `git` 版本(使用 `git --version` 查看) > `v1.8.0.0`. 有些文章中说 `v1.7.11` 就已经集成了, 实际上没有, 如果直接执行会看到这样的结果：

```cpp
git subtree  


git: 'subtree' is not a git command. See 'git --help'.
```

如果你是在 `OS X` 下使用 `git`, 推荐用 `homebrew` 来安装新版本


#2  subtree的使用
-------

针对第一段的3条需求, 我分别说明具体的命令. 


##2.1  创建 `subtree` 版本库
-------





*   第一次添加子目录, 建立与git项目的关联

建立关联总共有2条命令. 

语法：git remote add -f <子仓库名> <子仓库地址>

解释：其中-f意思是在添加远程仓库之后, 立即执行fetch. 

语法：git subtree add --prefix=<子目录名> <子仓库名> <分支> --squash

解释：--squash意思是把subtree的改动合并成一次commit, 这样就不用拉取子项目完整的历史记录. --prefix之后的=等号也可以用空格. 

示例


```cpp
git remote add -f ai git@github.com:aoxu/ai.git  
git subtree add --prefix=ai ai master --squash
```

##2.2 从远程仓库pull更新子目录
-------

更新子目录有2条命令. 

语法：git fetch <远程仓库名> <分支>

语法：git subtree pull --prefix=<子目录名> <远程分支> <分支> --squash

示例

```cpp
git fetch ai master  
$git subtree pull --prefix=ai ai --squash
```

或者

```cpp
git subtree pull --prefix=ai --squash git@github.com:aoxu/ai.git master
```


##2.3  从子目录push到远程仓库
-------

推送子目录的变更有1条命令. 

语法：git subtree push --prefix=<子目录名> <远程分支名> 分支

示例

```cpp
git subtree push --prefix=ai ai master
```

#3  参考资料：

[speackerdeck](https://speakerdeck.com/cloudsben/git-subtree-ti-dai-git-submodule)

[atlassian](https://speakerdeck.com/cloudsben/git-subtree-ti-dai-git-submodule)


[pro git](http://git-scm.com/book/zh/Git-%E5%B7%A5%E5%85%B7-%E5%AD%90%E6%A0%91%E5%90%88%E5%B9%B6)


[非常棒的 SubTree 教程](http://blog.charlescy.com/blog/2013/08/17/git-subtree-tutorial/)

[一个真实场景的使用例子](https://gist.github.com/kvnsmth/4688345)

[Git Submodule 和 Git SubTree](http://blogs.atlassian.com/2013/05/alternatives-to-git-submodule-git-subtree/)


![Git submodule 还是 Git Subtree](http://blog.zlxstar.me/blog/2014/07/18/git-submodule-vs-git-subtree/?utm_source=tuicool&utm_medium=referral)

![使用GIT SUBTREE集成项目到子目录](http://aoxuis.me/post/2013-08-06-git-subtree)

http://www.cjjjs.com/paper/czxt/20161215202120669.html




