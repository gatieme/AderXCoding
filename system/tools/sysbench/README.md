AderXCoding
=======

| CSDN | GitHub |
|:----:|:------:|
| [Aderstep--紫夜阑珊-青伶巷草](http://blog.csdn.net/gatieme) | [`AderXCoding/system/tools`](https://github.com/gatieme/AderXCoding/tree/master/system/tools) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 欢迎转载, 转载请注明出处, 谢谢支持
<br>


http://blog.chinaunix.net/uid-7589639-id-4126046.html

https://github.com/google/benchmark

http://www.memorybenchmark.net/

http://www.2cto.com/os/201307/231365.html

https://launchpad.net/sysbench/

http://imysql.cn/node/312

http://www.tuicool.com/articles/iQFF3i

http://project-management-knowledge.com/definitions/s/schedule-performance-index/

http://blog.csdn.net/xin15200793067/article/details/16358471

http://www.cs.umb.edu/~eb/goalmode/

#1	sysbench 简介
-------


`Sysbench` 是一种系统性能 `benchmark`

`SysBench` 是一款开源的、跨平台的、模块化的、多线程的性能测试工具, 通过高负载地运行在数据库上, 可以执行 `CPU`/内存/线程/`IO`/数据库 等方面的性能测试. 用于评估操作系统的性能参数.



主要用于评估测试各种不同系统参数下的数据库负载情况. 它主要包括以下几种方式的测试 :



| 编号 | 测试 |
|:---:|:---:|
| 1 | `cpu` 性能 |
| 2 | 磁盘io性能 |
| 3 | 调度程序性能 |
| 4 | 内存分配及传输速度 |
| 5 | `POSIX` 线程性能 |
| 6 | 数据库性能(`OLTP`基准测试) |

本来 `sysbench` 主要是为 `mysql` 编写的 `benchmark`. 但是现在 `SysBench` 将进一步扩展, 以支持更多的数据库 `backends`, `distributed`, `benchmarks`和第三方插件模块.


`sysbench` 按照指定的数量开启线程, 每个线程与 `mysql` 建立一个连接, 每个线程不停地进行事务操作, 打开事务, 然后进行一些查询、更新、插入操作, 提交事务, 再开始新的事务; 所有的 `sql` 只访问一个表-`sbtest`, 是由 `sysbench` 的 `prepare` 命令建好的. 其中的记录数, 也是在 `prepare` 时指定好并创建的. 测试结束, 会有一个统计结果, 包括例如每秒事务数、平均响应时间等等;



#2	`sysbench` 下载与安装
-------


##2.1	**项目地址**
-------

目前 `sysbench` 代码托管在 `launchpad` 和 `github
` 上

项目地址：

launchpad : https://launchpad.net/sysbench

github : https://github.com/akopytov/sysbench

>原来的官网 http://sysbench.sourceforge.net 已经不可用), 源码采用bazaar管理.


##2.2	**使用系统源安装**
-------


如果是 `Ubuntu` 系统

```cpp
sudo apt-get install sysbench
```

![使用系统源安装](ubuntu-install-sysbench.png)


##2.3	使用源码包编译安装
-------

**下载**

下载地址 :

https://github.com/akopytov/sysbench/archive/0.5.zip

**获得 `sysbench-0.5.zip`**

```cpp
wget https://github.com/akopytov/sysbench/archive/0.5.zip
unzip 0.5.zip
cd sysbench-0.5
```

![获得 `sysbench-0.5.zip](download-sysbench-src.png)

**安装**

```cpp
./autogen.sh
./configure
make
```

默认支持 `MySQL`, 如果需要测试 `Oracle/PostgreSQL`, 则在 `configure` 时需要加上 `–with-oracle` 或者 `–with-pgsql` 参数

如果需要测试 `mysql`, 则需要配置参数选项：

```cpp
./configure \
--with-mysql-includes=/opt/mysql/include/mysql #  表示mysql头文件目录  \
--with-mysql-libs=/opt/mysql/lib/mysql #  表示mysql模块目录
```

如果缺少 `libtool` 请至  ftp://ftp.gnu.org/gnu/libtool/ 下载


#3	测试
-------


编译成功之后, 就要开始测试各种性能了, 测试的方法官网网站上也提到一些, 但涉及到 `OLTP` 测试的部分却不够准确. 在这里我大致提一下


1	cpu性能测试

sysbench --test=cpu --cpu-max-prime=20000 run
cpu测试主要是进行素数的加法运算，在上面的例子中，指定了最大的素数为 20000，自己可以根据机器cpu的性能来适当调整数值。

2	线程测试

```cpp
sysbench --test=threads --num-threads=64 --thread-yields=100 --thread-locks=2 run
```

3	磁盘IO性能测试

```cpp
sysbench --test=fileio --num-threads=16 --file-total-size=3G --file-test-mode=rndrw prepare
sysbench --test=fileio --num-threads=16 --file-total-size=3G --file-test-mode=rndrw run
sysbench --test=fileio --num-threads=16 --file-total-size=3G --file-test-mode=rndrw cleanup
```

上述参数指定了最大创建16个线程，创建的文件总大小为3G，文件读写模式为随机读

4	内存测试

```cpp
sysbench --test=memory --memory-block-size=8k --memory-total-size=4G run
```

上述参数指定了本次测试整个过程是在内存中传输 4G 的数据量，每个 block 大小为 8K。

5	OLTP测试

```cpp
sysbench --test=oltp --mysql-table-engine=myisam --oltp-table-size=1000000 \
--mysql-socket=/tmp/mysql.sock --mysql-user=test --mysql-host=localhost \
--mysql-password=test prepare
```


上述参数指定了本次测试的表存储引擎类型为 myisam，这里需要注意的是，官方网站上的参数有一处有误，即 --mysql-table-engine，官方网站上写的是 --mysql-table-type，这个应该是没有及时更新导致的。另外，指定了表最大记录数为 1000000，其他参数就很好理解了，主要是指定登录方式。测试 OLTP 时，可以自己先创建数据库 sbtest，或者自己用参数 --mysql-db 来指定其他数据库。--mysql-table-engine 还可以指定为 innodb 等 MySQL 支持的表存储引擎类型。


<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
<br>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可
