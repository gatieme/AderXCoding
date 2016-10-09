Python的包管理工具Pip


| CSDN | GitHub |
|:----:|:------:|
| [Ubuntu安装Python的包管理工具Pip](http://blog.csdn.net/gatieme/article/details/48555711) | [`AderXCoding/system/tools/pip`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/pip) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可
<br>



>参考
>https://pypi.python.org/pypi/setuptools/
>https://pypi.python.org/pypi/pip#downloads


#1	安装pip
-------

#1.1	使用源安装
-------

```cpp
sudo apt-get install python-setuptools python-pip
```


#1.2	源码编译安装
-------

**下载pip**


```
wget https://pypi.python.org/packages/source/p/pip/pip-7.1.2.tar.gz#md5=3823d2343d9f3aaab21cf9c917710196
```

**编译安装**

先解压缩
```
tar -zxvf  pip-7.1.2.tar.gz
cd pip-7.1.2
```
使用如下命令编译安装
```
sudo python setup.py install
```

>pip需要easy_installer工具setuptools包支持,如果提示setuptools错误,请下载安装setuptools
>```
>wget https://bootstrap.pypa.io/ez_setup.py -O - | sudo python
>```

#1.3	使用配置好的脚本
-------

```cpp
curl "https://bootstrap.pypa.io/get-pip.py" -o "get-pip.py"

python get-pip.py
```

#2	使用pip
-------


##2.1	pip安装包
-------

```
pip install SomePackage
```

##2.2	pip查看已安装的包
-------
```
pip show --files SomePackage
```

##2.3	pip检查哪些包需要更新
-------
```
pip list --outdated
```

##2.4	pip升级包
```
pip install --upgrade SomePackage
```

##2.5	pip卸载包
```
pip uninstall SomePackage
```

##2.6	一行命令升级所有pip安装的Python包
-------

```cpp
pip freeze --local | grep -v '^\-e' | cut -d = -f 1  | xargs pip install -U
```

建议在执行前先执行：
```cpp
pip install -U distribute
```

补充：
由于使用了mysql-connector-python的包，

在安装时要使用 --allow-external mysql-connector-python 参数，所以在升级时，也应该加上该参数，命令行为：
```cpp
pip install -U distribute && pip freeze --local | grep -v '^\-e' | cut -d = -f 1  | xargs pip install -U --allow-external mysql-connector-python
```