Ubuntu环境下OpenGrok的安装及使用
=======


#1	OpenGrok介绍
-------


`OpenGrok`是一个快速, 便于使用的源码搜索引擎与对照引擎, 它能够帮助我们快速的搜索、定位、对照代码树. 接下来就具体讲解一下OpenGrok的安装及使用.



#2	安装OpenGrok
-------

##2.1	安装JAVA运行环境
-------

##2.2	安装Web服务器-Tomcat
-------

首先大家应该明白 `OpenGrok` 是一个 `Web` 系统, 因此要共享 `OpenGrok` 搜索引擎, 需要安装 `Web` 服务器.

在 `Ubuntu` 环境下, 推荐使用 `Tomcat`.

`Ubuntu14.04` 的源中已经提供了`Tomcat 7` 的包, 参见 

http://packages.ubuntu.com/trusty/tomcat7

*	安装 `Tomcat7`, 直接从源中安装 `Tomcat7`.



```cpp
sudo apt-get install tomcat7
```

*	启动 `Tomcat7`

```cpp
sudo service tomcat7 start
```

或者

```cpp
sudo /etc/init.d/tomcat7 start
```


启动 `Tomcat` 服务后, 在浏览器中输入网址

http://localhost:8080

能够进入以下页面证明Tomcat运行成功.


##2.3	安装OopenGrok
-------


安装好 `Tomcat` 后, 接下来就是配置 `OpenGrok` 了.

`OpenGrok` 下载地址 :

http://opengrok.github.io/OpenGrok

在该网址中可以下载 `OpenGrok` 的编译文件, 也可以下载源文件. 在此我们直接下载编译文件(对OpenGrok感兴趣的同学可以下载源码查看究竟）, 下载后通过以下命令进行解压：

```cpp
tar xvzf opengrok-0.11.1.tar.gz
```
解压完成后进入到解压目录, 将./lib目录下的source.war包拷贝到/data_2/tools/apache-tomcat-7.0.40/webapps目录下, 在浏览器中输入http://localhost:8080/source/网址（备注：war包会自动解压）看到以下界面证明OpenGrok运行成功. 

接下需要更改/data_2/tools/apache-tomcat-7.0.40/webapps/source/WEB-INF目录下的web.xml配置文件
[html] view plain copy
<context-param>  
   <param-name>CONFIGURATION</param-name>  
   <param-value><span style="color:#ff0000;">/data_2/tools/opengrok-0.11.1/</span>etc/configuration.xml</param-value>  
   <description>Full path to the configuration file where OpenGrok can read it's configuration</description>  
 </context-param>  
其中红色标注的为上文OpenGrok解压路径. 最后就是建立源码的索引. 进入～./opengrok-0.11.1/bin 目录 执行以下命令建立源码索引：
[python] view plain copy
#./OpenGrok index /data/code  
（备注：/data/code/ 为目标索引路径）