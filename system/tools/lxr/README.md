Ubuntu14.04搭建LXR本地服务器阅读Linux内核代码
=======

| CSDN | GitHub |
|:----:|:------:|
| [Ubuntu下apache的安装与配置](http://blog.csdn.net/gatieme) | [`AderXCoding/system/tools`](https://github.com/gatieme/AderXCoding/tree/master/system/tools) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处
<br>



我开始打算使用 `apache2 + mysql  + lxr` 搭建的. 毕竟嘛网上教程都是这个, 有点坑爹的是网上的教程都是以前的, 和现在的好多软件包不一样, 偶尔发现个2014年的博客看了下居然还是照搬他人的.

上面居然还能用
```cpp
sudo apt-get install lxr
```
表示呵呵了. 花了大量时间摸索着也没能用apapche2 搭建起来.

因为 `Apache2` 的 `mod_perl` 模块不能很好的工作, 当打开

```cpp
http：//localhost/lxr/source
```

时候出现的是 `source` 文件里面的内容, 而不是执行改文件（我没有找到好的解决方法)!

所以就放弃这个了, 自己使用 `lxr` 里面的 `install` 文档摸索着用 `ighttpd + mysql  + lxr` 搭建 `lxr` 本地服务器


http://blog.sina.com.cn/s/blog_c3884f930102v6as.html

http://brucewuu.lofter.com/post/a6819_3aead51

http://memyselfandtaco.blogspot.com/2008/06/technical-writings-rule-of-thumb-local.html


#1	安装lxr
-------

##1.1	安装依赖包
-------


先安装需要的包 :

```cpp
#ctags swish-e perl
sudo apt-get install exuberant-ctags swish-e perl

# mysql-server | MariaDB | 任选其一
sudo apt-get install mysql-server
sudo apt-get install mariadb-server

#apache2 | lighttpd
sudo apt-get install apache2
sudo apt-get install lighttpd*
```

| 包 | 描述 |
|:--:|:---:|
| mysql-server或者MariaDB | mysql服务器, 任选其一即可 |
| lighttpd或者apache2 | lighttpd或者apache2服务以及相应的服务模块, 任选其一即可, 如果选择了apache请安装 `libapache2-mod-perl2-dev |
| swish-e或者glimpse | 任选其一即可 |
| perl | 也是配置需要实际没有用到的，如果没有不能通过配置前的检查就不能往下执行 |


下载linux源文件：解压到后面需要配置的文件目录(自己定), 文件名改为相应的版本号例如 `linux-3.18` 改完 `3.18`


##1.2	下载安装glimpse
-------

网址：http://webglimpse.net

下载后解压到自己需要的目录, 例如`/usr/local`

```cpp
wget http://webglimpse.net/trial/glimpse-latest.tar.gz
tar -zxvf glimpse-latest.tar.gz
#下载完成后版本为glimpse-4.18.6
```

![glimpse-4.18.6](glimpse-latest.png)



进入glimpse目录, 编译并安装

```cpp
./configure --prefix=/usr/local
make
sudo make install
```


执行过程中可能还其他依赖包, 根据提示进行安装, 安装完成后使用

```cpp
glimpse --help
which glipmse
glimpse -V
```

来验证 `glimpse` 的安装


![安装glimpse](glimpse-install.png)



##1.3	下载安装lxr(我的是2.03版本)
-------

网址：http://sourceforge.net/projects/lxr/files/latest/download?source=files

下载完成后解压到/usr/local/share (install文档建议目录)

改名成lxr

进入lxr根目录：

```cpp
cd /usr/local/share/lxr
```

执行genxref检查lxr的配置环境

```cpp
./genxref --checkonly
```
这个是为了检查LXR配置环境，根据提示缺少什么再安装什么，执行后显示如下：


##1.4	下载安装lxrng
-------


网站 :
git	:

```cpp
```