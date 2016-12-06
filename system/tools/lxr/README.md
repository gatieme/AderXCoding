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


#1	LXR(Linux Cross Referencer)介绍
-------

LXR 项目站点 : http://lxr.sourceforge.net/zh/index.php

源码下载 : http://sourceforge.net/projects/lxr

安装教程 : http://lxr.sourceforge.net/en/1-0-InstallSteps/1-0-install.php

`LXR` 是一个通用的源代码索引器和交叉引用器 它提供了一个基于 web 的可浏览任意定义以及任意标识的用法。 它支持很多种语言。

LXR 曾经被作为 “Linux 交叉引用器” 但是已经被证明它可以用来作为任意基于 Linux 内核的项目的交叉引用
它基于股票网站技术 （这意味着它的输出是标准的 HTML） 所以可以选择任意的可用 web 浏览器来作为他的客户端。 它被设计为不依赖 java 或者任何第三方客户端脚本，这样可以保证系统需求和依赖的最小化。

人们经常问起 LXR 与 LXRng （见于 http://lxr.linux.no） 之间的差别。 LXRng 是从 LXR 中 fork 出来带有实验性质的用来探索其他技术的分支。 它基于 ajax 并且依赖很多 CPAN 的包。 它使用了很多的客户端脚本，这意味着运算的负载被服务端和客户端一起分担了。
CAUTION!

It looks like lxr.linux.no has closed without notice some time during the first half of 2014. Whether there is a backup of LXRng is unknown.

在服务端， 任意的带有 cgi 能力的 web 服务器都能表现的很好。

在开发过程中，LXR 是一个很有价值的项目合成观察角色。 对于从头开始学习源代码的人来说，它也是一个很有用的工具。 否则，学习曲线会很陡峭。




#1	安装lxr
-------

*	检查并安装运行环境以及依赖包

*	安装lxr

*	配置lxr



##1.1	检查并安装运行环境以及依赖包
-------

| 包 | 描述 |
|:--:|:---:|
| mysql-server或者MariaDB | mysql服务器, 任选其一即可 |
| lighttpd或者apache2 | lighttpd或者apache2服务以及相应的服务模块, 任选其一即可, 如果选择了apache请安装 `libapache2-mod-perl2-dev |
| swish-e或者glimpse | 任选其一即可 |
| perl | 也是配置需要实际没有用到的，如果没有不能通过配置前的检查就不能往下执行 |

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



##1.1.1	安装并检查ctags
-------


LXR 要求ctags版本大于5.0

```cpp
sudo apt-get install exuberant-ctags

ctags --version
```

![ctags的版本检查](ctags-version.png)

下载linux源文件：解压到后面需要配置的文件目录(自己定), 文件名改为相应的版本号例如 `linux-3.18` 改完 `3.18`


##1.1.2	安装并检查perl
-------


`ubuntu 14.04` 默认已安装了`perl`, `LXR-2.1.0` 要求`perl` 版本大于 `v5.10` 即可


```cpp
sudo apt-get install perl

perl -v
```


![perl的版本检查](perl-version.png)

`LXR` 的很多配置都是通过 `perl` 来完成的, 因此我们需要安装一些其他的 `perl` 模块, 具体的信息参见[其他perl模块](带填入网站链接)



##1.1.3	安装并检查关系型数据库
-------


配置LXR需要数据库的支持, 可以使用 `mariadb`或`MySQL 4.X／5.x`、`Oracle`、`PostgreSQL` 和`SQLite`等, 任选其一即可, 我使用了`mariadb-5.5`

```cpp
sudo apt-get install mariadb-server
```

如果你希望安装10.0版本, 则14.04上需要添加源

```cpp
sudo apt-get install software-properties-common
sudo apt-key adv --recv-keys --keyserver hkp://keyserver.ubuntu.com:80 0xcbcb082a1bb943db
sudo add-apt-repository 'deb [arch=amd64,i386,ppc64el] http://mirrors.tuna.tsinghua.edu.cn/mariadb/repo/10.0/ubuntu trusty main'
```

具体信息请参见[`Ubuntu 14.04`(`Trusty`)安装`MariaDB 10`数据库](http://blog.csdn.net/gatieme/article/details/53048071)

自然我们也需要perl连接数据库的接口`Perl DBI drivers`, 这个我们会在后面讲解其他模块时候进行详细详解




##1.1.4	http服务器
-------


LXR将我们的源代码处理成为网站的形式, 自然就需要http服务器, 最常用的是`Apache httpd`, 当然也有很多用`Lighttpd`是替代选择的, 但是LXR从v2.0开始, 支持`Nginx`和`thttpd`等服务.


`http`服务器我选择的是 `apache2`


```cpp
sudo apt-get install apache2
```

详细信息请参见[Ubuntu下apache的安装与配置](http://blog.csdn.net/gatieme/article/details/53025505)


##1.1.5	索引系统`glimpse`或者`swish-e`
-------


glimpse(http://webglimpse.net)和swish-e(http://swish-e.org/), 建立索引数据的工具, 安装一个即可.

*	安装`swish-e`

`Swish-e`是一个快速, 灵活和自由开放源码的网页索引系统. `Swish-e`是适合收藏的`100`万或更小的网页文件. 使用`Gnome ™ libxml2`分析器和收集过滤器, `Swish-e`能索引的纯文本文件, 电子邮件, `PDF`格式, `HTML`格式, `XML`和`微软®Word`, `PowerPoint`, `Excel`和任何文件, 可以转换为`XML`或`HTML`文档. `Swish-e`也往往用做为数据库的功能补充, 如`MySQL®`数据库的非常快的全文检索



```cpp
sudo apt-get install swish-e
swish-e -V
```

![swish的版本信息](swish-version.png)


*	安装`glimpse`


`Glimpse`除了对数据库建立检索信息, 其高级工具`webglimpse` 还包含了一个对你的 `Web` 服务器应用进行诊断的客户端工具.

`Glimpse` 允许你调试你的 `Web` 服务, `Firebug` 是客户端代码的调试, 而 `Glimpse` 是服务器端代码调试.


网址：http://webglimpse.net

首先下载源码包并解压

```cpp
wget http://webglimpse.net/trial/glimpse-latest.tar.gz
#下载完成后版本为glimpse-4.18.6

tar -zxvf glimpse-latest.tar.gz
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



##1.1.6	其他perl模块
-------

>	**提示与建议**
>
> LXR的很多配置都是给予perl脚本来运行的, 因此我们在后期需要安装很多perl的模块, 包括数据库驱动`perl DBI`和`httpd modules`等, 而往往有时候我们并不知道这个perl模块的包名叫什么, 这时候就需要一些工具或者技巧来为我们助力
>
>
>参见[How to install Perl on Ubuntu Server?](http://superuser.com/questions/362990/how-to-install-perl-on-ubuntu-server)
>
>*	使用cpan来管理和安装perl模块
>
>	CPAN（Comprehensive Perl Archive Network）中译为“Perl综合典藏网”，“Perl综合档案网”或者“Perl程序库”。CPAN它包含了极多用Perl写成的软件和其文件
>	```cpp
>	sudo apt-get install cpanminus
>	```
>
>	安装后使用如下命令即可安装模块
>	```cpp
>	cpan App::cpanminus
>	```
>
>	比如安装File::MMagic和Perl DBI
>	```cpp
>	cpanm DBI
>	cpanm File::MMagic
>	```
>
>	有关cpan的文档可参考：http://www.cpan.org/modules/INSTALL.html
>
>
>*	使用apt-cache从源中搜索包
>	```cpp
>	apt-cache search perl <module-name>
>	```
>
>	比如安装
>	```cpp
>	apt-cache search perl DBD-mysql
>	apt-cache search perl DBD-Pg
>	```
>	libdbd-mysql-perl - Perl5 database interface to the MySQL database
>	libdbd-pg-perl - Perl DBI driver for the PostgreSQL database server
>
>	搜索出来以后直接用`apt-get install`安装即可



*	perl DBI数据库驱动和对应数据库的驱动

参见　http://dev.mysql.com/downloads/dbi.html

```cpp
cpanm DBI
```

或者

```cpp
########
# 安装dbi接口
########
apt-cache search perl dbi-perl
#输出
#libdbi-perl - Perl Database Interface (DBI)
sudo apt-get install libdbi-per
########

# 安装对应数据库的DBD driver
########
apt-cache search perl DBD-mysql
#输出
#libdbd-mysql-perl - Perl5 database interface to the MySQL database
#
sudo apt-get install libdbd-mysql-perl
```

*	perl File::MMagic module

```cpp
cpanm File::MMagic
```

或者使用如下命令安装File::MMagic

```cpp
sudo apt-cache search perl file mmagic
#输出
#libfile-mmagic-perl - Perl module to guess file type
#libfile-mmagic-xs-perl - Perl module to guess file type (à la mod_mime_magic)


apt-get install libfile-mmagic-perl
```


*	其他 `perl` 模块


如果你使用 `postgresql`, 请使用如下


安装数据库

```cpp
sudo apt-get install postgresql-8.3 postgresql-client-8.3
```

安装模块

```cpp
sudo apt-get install libxapian15 libsearch-xapian-perl libapache2-mod-perl2 libcgi-simple-perl libcgi-ajax-perl libhtml-parser-perl libtemplate-perl libterm-progressbar-perl libdevel-size-perl libdbd-pg-perl
```

##1.2	下载安装lxr
-------


###1.2.1	下载lxr的源代码
-------



下载地址  : http://sourceforge.net/projects/lxr/files/latest/download?source=files


下载完成后解压到`/usr/local/share`, (install文档建议目录), 但是为了方便管理我解压在了 `/opt` 下

解压后的目录如下图所示, `doc`中包含了所有的文档信息,  `INSTALL` 安装建议文件就在此目录


![lxr的目录结构](lxr-directory.png)




执行genxref检查lxr的配置环境

```cpp
./genxref --checkonly
```
这个是为了检查LXR配置环境，根据提示缺少什么再安装什么，执行后显示如下

![执行genxref检查lxr的配置环境](genxref--checkonly.png)

可以看到

1.	我们需要先配置一份 `lxr.conf` 的配置文件

2.	由于我们同时安装了 `swish-e` 和 `glimpse`, 因此需要设置使用哪个


##1.2.2	生成配置文件
-------

可以使用 `scripts/configure-lxr.pl` 脚本来生成默认的配置文件, 执行如下命令

```cpp
./scripts/configure-lxr.pl -vv
```

配置的过程如下

```cpp
10:07 gatieme@Aspire:lxr $sudo ./scripts/configure-lxr.pl -vv
*** LXR configurator (version: 2.1) ***

LXR root directory is /opt/lxr
Configuration will be stored in custom.d/
directory custom.d created

#  单树模式还是多树模式, 慎选, 此选项无法通过配置文件来修改
#  如果想要修改只能删除所有的数据库重新来过
#  如果只希望索引一个源码和host的话选择S即可
Configure for single/multiple trees? [S/m] > m

*** LXR web server configuration ***

Many different configurations are possible, they are related to the way
LXR service is accessed, i.e. to the structure of the URL.
Refer to the User's Manual for a description of the variants.

LXR can be located at the server-root (so called dedicated)
or lower in the server hierarchy (shared because there are
usually other pages or sections).
# 这里我默认
Server type? [dedicated/SHARED] > SHARED

Selecting which tree to display can be done in various ways:
  1. from the host name (all names are different),
  2. from a prefix to a common host name (similar to previous)
  3. from the site section name (all different)
  4. from interpretation of a section name part (similar to previous)
  5. from the head of script arguments
Method 5 is highly recommended because it has no impact on webserver
  configuration.
Method 3 is second choice but involves manually setting up many
  symbolic links (one per source-tree).
Method 1 & 2 do not involve symbolic links but need populating webserver
  configuration with virtual hosts.
  Note that method 2 does not work well on //localhost.
Method 4 is deprecated because it has proved not easily portable
  under alternate webservers (other than Apache).

# 这里我默认
Tree designation? [ARGUMENT
/section name
/prefix in host
/hostname
/embedded in section] > 

The computer hosting the server is described by an URL.
The form is scheme://host_name:port
where:
  - scheme is either http or https (http: can be omitted),
  - host_name can be given as an IP address such as 123.45.67.89
              or a domain name like localhost or lxr.url.example,
  - port may be omitted if standard for the scheme.
--- Host name or IP? [//localhost] > 
--- Alias name or IP? > http://mylxr.com
--- Alias name or IP? > 
URL section name for LXR in your server? [/lxr] > /lxr
Will it be shared by all trees? [YES/no] > yes

*** LXR database configuration ***


The choice of the database engine can make a difference in indexing performance,
but resource consumption is also an important factor.
  * For a small personal project, try SQLite which do not
    need a server and is free from configuration burden.
  * For medium to large projects, choice is between MySQL,
    PostgreSQL and Oracle.
    Oracle is not a free software, its interface has not been
    tested for a long time.
  * PostgreSQL databases are smaller than MySQL's
    and performance is roughly equivalent.
  * MySQL is at its best with large-sized projects
    (such as kernel cross-referencing) where it is fastest at the cost
    of bigger databases.
  * Take also in consideration the number of connected users.
#  选择什么数据库
Database engine? [MYSQL/oracle/postgres/sqlite] > MYSQL
The safest option is to create one database per tree.
You can however create a single database for all your trees with a specific set of
tables for each tree (though this is not recommended).
#  使用全局数据库还是每课树一个数据库
#  比较保险的选项是PER TREE, 这样的话各个树的数据互相不干扰
#  但是我为了方便管理, 选择了global
How do you setup the databases? [PER TREE/global] > global
Name of global database? [lxr] > lxr
All databases can be accessed with the same username and
can also be described under the same names.
Will you share database characteristics? [YES/no] > YES
#  数据库的用户名和密码默认就行
--- DB user name? [lxr] > lxr
--- DB password ? [lxrpw] > lxrpw
#  glimpse/swish-e数据的存储路径
--- Directory for glimpse databases? > /opt/lxr/database/glimpse
--- Directory for swish-e databases? > /opt/lxr/database/swish-e
REMINDER: after this configuration step, open lxr.conf
and comment out one of 'glimpsebin' or 'swishbin'.

file .htaccess written into LXR root directory
file apache2-require.pl written into configuration directory
file apache-lxrserver.conf written into configuration directory
ERROR: unknown %virtroot% substitution marker!
ERROR: unknown %virtroot% substitution marker!
file lighttpd-lxrserver.conf written into configuration directory
file nginx-lxrserver.conf written into configuration directory
file thttpd-lxrserver.conf written into configuration directory
Mercurial support files written into configuration directory

*** LXR master configuration file setup ***
    Global section part

*** Configuring auxiliary tool paths
*** Host name previously defined as http://localhost
*** Configuring HTML parameters
*** 'Buttons-and-menus' interface is recommended for the kernel
*** to avoid screen cluttering.
--- Use 'buttons-and-menus' instead of 'link' interface? [YES/no] > YES
*** Configuring file subsection
*** Configuring "common factors"
*** Marking tree section

*** LXR master configuration file setup ***
    Tree section part
    SQL script for database initialisation

*** Configuring LXR server parameters
*** The virtual root is the fixed URL part after the hostname.
*** You previously defined the virtual root as /lxr
--- Caption in page header? (e.g. Project XYZZY displayed by LXR) > gatieme-lxr
Do you want a speed switch button for this tree ? [YES/no] > YES
--- Short title for button? (e.g. XYZZY) > speed-gatieme
--- Tree identification in URL? (e.g. the-tree) > the-tree
Do you need a specific encoding for this tree ? [yes/NO] > yes
--- Encoding name? (e.g. iso-8859-1) > UTF-8
*** Describing tree location
How is your tree stored? [FILES/cvs/git/svn/hg/bk] > FILES
*** A source directory contains one sub-directory for every version.
--- Source directory? (e.g. /home/myself/project-tree) >  /opt/lxr/database/source
Name to display for the path root? (e.g. Project or $v for version) [$v] > 
*** Enumerating versions
Label for version selection menu?  [Version] > 
  * Versions can be explicitly enumerated, be read from a file or computed
*** by a function. The latter case is recommended for VCS-stored trees.
Version enumeration method? [LIST/file/function] > 
--- Version name?  > 4.4.6
--- Version name? (hit return to stop) > 
*** By default, first version in list is displayed. You may also indicate
*** a prefered version.
--- Default displayed version is first in 'range'? [YES/no] > YES
*** Setting directory lists
*** Some directories may contain non-public project data (binaries,
*** compilers caches, SCM control data, ...). They can be hidden from LXR.
--- Directory to ignore, e.g. CVSROOT or CVS? (hit return to stop) >
*** If your source code uses "include" statements (#include, require, ...)
*** LXR needs hints to resolve the destination file.
--- Include directory, e.g. /include? (hit return to stop) >
*** Configuring data storage
#  数据库表的前缀, 命名规范的话删除很方便
--- DB table prefix? [lxr_] > lxr_

#  是否继续配置另外一颗树
*** Configure another tree? [YES/no] > no
configuration saved in custom.d/lxr.conf
DB initialisation sript is custom.d/initdb.sh

```

配置完成后, 会在 `lxr` 目录下生成一个 `custom.d`的目录用于存放生成的脚本和配置文件

![配置目录custom.d](custom-directory.png)



| 脚本/配置文件 | 描述 |
|:-----------:|:----:|
| lxr.conf | lxr的配置文件, 配置了源码树和数据库路径等信息 |
| initdb.sh | 创建数据库的脚本 |
| lxr.ctxt |  |
| hg-lxr-ext.py |  |
| hg.rc |   |
| apache2-require.pl |  |
| apache-lxrserver.conf |  |
| nginx-lxrserver.conf |  |
| lighttpd-lxrserver.conf |  |
| thttpd-lxrserver.conf |  |


关于配置选项的详细信息, 可以查看[Step 3: LXR and Database Configuration](http://lxr.sourceforge.net/en/1-0-InstallSteps/1-0-install3config.php)


##1.2.3	初始化数据库
-------


```cpp
sudo ./custom.d/initdb.sh
```

![执行脚本创建数据库](sh-initdb.png)

查看 `./custom.d/initdb.sh` 文件内容, 再登录到 `MySQL` 看 `lxr` 用户、`lxr` 数据库、表是否跟 `./custom.d/initdb.sh` 文件中的一致


![显示所有的数据库的信息](show-lxr-tables.png)


###1.2.4	配置文件
-------

拷贝刚刚生成的 `lxr` 配置文件

```cpp
sudo cp custom.d/lxr.conf .
```

注意由于我们需要从 `glimpse` 和 `swish-e` 中选择一个, 因此找到配置文件中如下信息, 注释掉不需要的

```cpp
	, 'glimpsebin'     => '/usr/local/bin/glimpse'
	, 'glimpseindex'   => '/usr/local/bin/glimpseindex'
	, 'glimpsedirbase' => '/opt/lxr/database/glimpse'
#	, 'swishbin'     => '/usr/bin/swish-e'
#	, 'swishdirbase' => '/opt/lxr/database/swish-e'
#	, 'swishconf' => '/opt/lxr/templates/swish-e.conf'

```

###1.2.5	配置源码
-------

现在我们配置已经完成了, 在生成源代码的索引之前, 我们需要一份完成的源代码的信息

依照之前的配置, 我们的源代码应该防止在sourceroot制定的目录, 即 `/opt/lxr/database/source/$v`, 我们现在要索引`linux-4.4.6`, 就需要将源代码拷贝到 `/opt/lxr/database/source/4.4.6`, 当然也可以做一个链接

```cpp
sudo ln -s  linux-linaro-stable-rt-4.4.6 /opt/lxr/database/source/4.4.6
```

###1.2.6	生成索引


```cpp
sudo ./genxref --url=http://localhost/lxr --version=4.4.6
```

或者

```cpp
sudo ./genxref --allurls 4.4.6
```


更加详细的信息请参见[Step 4: Populate LXR Database](http://lxr.sourceforge.net/en/1-0-InstallSteps/1-0-install4genxref.php)


等待配置完成即可, 等待的时间会很漫长

![生成索引信息](genxref-lxr.png)



###1.2.7	配置服务器
-------


拷贝apache的配置文件到apache2的配置目录

```cpp
sudo cp custom.d/apache-lxrserver.conf  /etc/apache2/conf-enabled/
```

重启apache2服务

```cpp
sudo service apache2 restart
```

其他服务器的配置请参见[Step 5: Configure the Web Server](http://lxr.sourceforge.net/en/1-0-InstallSteps/1-0-install5server.php)

###1.2.8	验证
-------

然后我们直接访问

http://localhost/lxr/source

或者之前绑定的本地域名

http://mylxr.com/source

即可

![`lxr` 搭建成功](lxr-success.png)

###1.2.9	可能遇到的问题
-------


一下, 参照  [`liuqiaoyu080512`](http://blog.csdn.net/liuqiaoyu080512) 提供的帮助


*	显示 `source` 源码 而, 不是运行结果

配置完成之后, 访问 http://localhost/lxr/source

发现浏览器中看到的是 `source` 的源码，而不是运行结果

![`lxr` 显示的是 `source` 的源码](lxr-source-error.png)


则说明 `cgi` 模块未开启, `cgi` 模块的信息请参见 `apache2`  配置目录下的 `mods-available` 和 `mods-enabled`.

```cpp
sudo a2enmod cgid
```

![开启 `cgid` 模块](apache-enable-cgid.png)


>新装的 `apache2` 由于当前的环境最后开启的是 `cgid` 模块，这个没关系, 功能应该跟 `cgi` 一样。


*	浏览器缓存的问题

至此已经配置成功了, 但是但是浏览器有一点很恶心, 先说一下：Firefox 会缓存页面，也许你配置已经成功了，但是 Firefox 直接展示缓存的页面，你看到的还是 source 文件的 perl 源码，
所以在判断是否配置成功前清除缓存：首选项->高级->网络->网络内容缓存 选立即清除。

*	`custom.d/apache-lxrserver.conf` 配置文件不管用



正常来说 `/etc/apache2/apache2.conf` 内部的如下两行, 会加载 `conf-enabled` 和 `sites-enabled` 下的所有配置文件

```cpp
# Include generic snippets of statements
IncludeOptional conf-enabled/*.conf

# Include the virtual host configurations:
IncludeOptional sites-enabled/*.conf
```

但是如果仍然出现 `custom.d/apache-lxrserver.conf` 的配置不管用, 因此可以直接修改了默认的配置文件 `/etc/apache2/sites-enabled/000-default.conf` 为


```cpp
<VirtualHost *:80>
ServerAdmin webmaster@localhost
DocumentRoot /var/www/html

# 这里开始是新增内容
ScriptAlias /lxr/ /opt/lxr/
<Directory "/opt/lxr/">
AllowOverride None
Options +ExecCGI -MultiViews +SymLinksIfOwnerMatch
Require all granted
AddHandler default-handler .jpg .png .css # 避免这些文件也被当做脚本执行
</Directory>
# 新增内容结束

ErrorLog ${APACHE_LOG_DIR}/error.log
CustomLog ${APACHE_LOG_DIR}/access.log combined

</VirtualHost>
```


##1.3	关于lxrng
-------


`lxrng` 是一个`lxr`的实验性分支, 添加了很多新的功能

关于lxrng的使用, 请参见

[Technical Writing's Rule Of Thumb + Local Web based Code Cross Reference (eg. LXR clone](http://memyselfandtaco.blogspot.com/2008/06/technical-writings-rule-of-thumb-local.html)




#	参考
-------


[Ubuntu 14.04 搭建LXR 本地服务器](http://blog.sina.com.cn/s/blog_c3884f930102v6as.html)

[ubuntu 12.04上安装LXR 0.11(zz)](http://brucewuu.lofter.com/post/a6819_3aead51)

[Technical Writing's Rule Of Thumb + Local Web based Code Cross Reference (eg. LXR clone](http://memyselfandtaco.blogspot.com/2008/06/technical-writings-rule-of-thumb-local.html)

[Install. Instructions](http://lxr.sourceforge.net/en/1-0-InstallSteps/1-0-install.php)

[源码阅读工具 lxr 安装配置初探](http://blog.csdn.net/duyiwuer2009/article/details/8958232)


codeinsight VS opengrok