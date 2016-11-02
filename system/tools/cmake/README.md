Ubuntu中安装cmake
=======

#1	ppa源安装
-------

添加`PPA`安装

```cpp
sudo add-apt-repository ppa:george-edison55/cmake-3.x
sudo apt-get update
```

如果你从来没装过cmake

```cpp
sudo apt-get install cmake
```

如果你装过cmake

```cpp
sudo apt-get upgrade
```

安装完后，用命令 : cmake --version 查看当前的cmake版本，可以看到现在cmake的版本为3.2.2


#2	使用官方的二进制包
-------



cmake的官方最新释放的稳定版本是3.6.2, 官方也为我们制作了二进制包

地址：https://cmake.org/download/
下载：https://cmake.org/files/v3.5/cmake-3.5.2-Linux-x86_64.tar.gz

下载二进制包

```cpp
wget https://cmake.org/files/v3.6/cmake-3.6.2-Linux-x86_64.tar.gz
```

解压缩

```cpp
sudo tar -zxvf cmake-3.6.2-Linux-x86_64.tar.gz -C /usr
```

#3	源码编译cmake
-------


下载源码包

```cpp
wget https://cmake.org/files/v3.6/cmake-3.6.2.tar.gz
tar -zxvf cmake-3.6.2.tar.gz
```


编译安装

```cpp
cd cmake3.6.2
./configure
make
sudo make install
```




