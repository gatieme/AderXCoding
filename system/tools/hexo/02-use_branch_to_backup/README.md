使用 Hexo 搭建 GitHub Page 博客(二)--备份至 GitHub 过程
=======

| CSDN | GitHub | Hexo |
|:----:|:------:|:----:|
| [使用 Hexo 搭建 GitHub Page 博客(二)--使用 GitHub 分支保存 Hexo 环境和博文](https://blog.csdn.net/gatieme/article/details/82317704) | [`AderXCoding/system/tools/hexo/02-use_branch_to_backup`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/hexo/02-use_branch_to_backup) |

<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>

本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作

因本人技术水平和知识面有限, 内容如有纰漏或者需要修正的地方, 欢迎大家指正, 也欢迎大家提供一些其他好的调试工具以供收录, 鄙人在此谢谢啦

<br>

#1  问题提出
-------

使用 `GitHub Page` 搭建个人博客, 经常会遇到一个问题.

我们的 `username.github.io` 的 master 分支, 保存了我们用 `Hexo` 生成的静态 `Html`. 那 `Hexo` 环境和博客的 `markdown` 源码, 怎么高校的保存呢?

最简单的方法就是用另外一个 `repo` 来保存我们的 `Hexo` 环境和源码, 我们称为 `Hexo repo`. 这样我们只需要将 `public` 目录重定向到实际的 `html repo` 就可以了. 这样子我们更新博客的方式就成为:

1.  在 `Hexo repo` 中编写和生成博客, 最后生成 `HTML`. 然后将修改 `git commit`, 就完成了 Hexo 环境和博客源码的保存.

2.  生成的 `HTML` 静态网页, 直接生成在 `username.github.io`, 我们同样 `git commit` 到 `master` 分支上之后, 访问网页就可以看到更新后的博客.

有没有更方便的方法呢, 我们考虑, 我们用 `master` 分支保存了 `Hexo` 生成的 `HTML` 网页, 那我们可以新建一个分支保存 `Hexo` 环境和 博文源代码.



##2 问题解决
-------

在 `github` 上新建一个 `GitHub Page : gatieme.github.io`. 在这个仓库下, 另外新增加一个 `hexo` 分支, 并且设置该分支为主分支.

[01-hexo_branch](https://github.com/gatieme/AderXCoding/blob/master/system/tools/hexo/01-use_hexo/01-xups_theme.png)

这样, `master` 用来上传 `hexo` 搭建的博客编译好的博客. `hexo` 分支用来备份源文件.


##2.1   **完整操作如下(首次搭建环境建议运行)**
-------


1. 创建仓库, gatieme.github.io

2. 创建两个分支： master 与 hexo, 设置hexo为默认分支(因为我们只需要手动管理这个分支上的Hexo网站文件) 

3. 将 gatieme.github.io.git 仓库 clone 到本地

4. 如果是首次搭建环境, 则需要安装 hexo 的编译和处理环境
    在本地仓库下通过依次执行
    npm install hexo
    hexo init
    npm install
    npm install hexo-deployer-git

5. 配置 `Hexo` 的 `deploy`.
    配置 `_config.yml` 中的 `deploy` 参数, 分支应为 `master`.
    
    ```
    # Deployment
    ## Docs: https://hexo.io/docs/deployment.html
    deploy:
        type: git
        repo: git@github.com:gatieme/gatieme.github.io.git
        branch: master
    ```

6. 每次修改或者新增博文后, 将博客的源码提交到 `Hexo` 分支.
    依次执行 git add .、git commit -m “…”、git push origin hexo 提交网站相关的文件

7. 执行 hexo generate -d 生成网站并部署到 GitHub 上。


##2.2   **日常博文修改**
-------

第一次配置完成后, 以后只需要循环进行 `6-7` 操作即可.


在本地对博客进行修改添加新博文、修改样式等等后. 通过下面的流程进行管理：

1.  依次执行git add .、git commit -m “…”、git push origin hexo指令将改动推送到GitHub (此时当前分支应为hexo)

2.  然后才执行 hexo generate -d 发布网站到 master 分支上.


##2.3   本地资料丢失 
-------

当重装电脑之后，或者想在其他电脑上修改博客，可以使用下列步骤 :

1.  将 gatieme.github.io 仓库 clone 到本地

    git clone git@github.com:gatieme/gatieme.github.io.git 拷贝仓库(默认分支为hexo) 

2.  在本地重新安装 `Hexo` 编译环境.
    通过Git bash依次执行下列指令:
    npm install hexo
    npm install
    npm install hexo-deployer-git

>注意:
>
>hexo init 会初始化 Hexo 环境, 该操作会清空.git 文件夹, 导致版本控制信息会丢失. 
>
>因此除了首次搭建环境之外, 无需运行此命令.
>
>如果万不得已出现 `Hexo` 环境损坏, 需要重新初始化, 可以先拷贝出 `.git` 文件夹, 然后搭建环境并初始化之后, 将 .git 信息重新拷贝回来.


#3  参考资料
-------

[使用hexo，如果换了电脑怎么更新博客？](https://www.zhihu.com/question/21193762)
 

[GitHub Pages + Hexo搭建博客](http://crazymilk.github.io/2015/12/28/GitHub-Pages-Hexo%E6%90%AD%E5%BB%BA%E5%8D%9A%E5%AE%A2/#more)

[【GitHub】创建Git分支将Hexo博客迁移到其它电脑](https://blog.csdn.net/White_Idiot/article/details/80685990)

<br>

*	本作品/博文 ( [AderStep-紫夜阑珊-青伶巷草 Copyright ©2013-2017](http://blog.csdn.net/gatieme) ), 由 [成坚(gatieme)](http://blog.csdn.net/gatieme) 创作.

*	采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可. 欢迎转载、使用、重新发布, 但务必保留文章署名[成坚gatieme](http://blog.csdn.net/gatieme) ( 包含链接: http://blog.csdn.net/gatieme ), 不得用于商业目的. 

*	基于本文修改后的作品务必以相同的许可发布. 如有任何疑问，请与我联系.
