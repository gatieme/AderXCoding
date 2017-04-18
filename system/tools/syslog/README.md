ubuntu /var/log/下各个日志文件描述及修复无message文件和debug文件
=======

| CSDN | GitHub |
|:----:|:------:|
| [ubuntu /var/log/下各个日志文件描述及修复无message文件和debug文件](http://blog.csdn.net/gatieme/article/details/68951962) | [`AderXCoding/system/tools/syslog`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/syslog) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作
<br>

本文简单介绍ubuntu/var/log/下各个日志文件，方便出现错误的时候查询相应的log


#1	日志文件描述
-------


| 日志 | 描述 |
|:---:|:----:|
| alternatives.log | 更新替代信息都记录在这个文件中 |
| apport.log | 应用程序崩溃记录 |
| apt | 用apt-get安装卸载软件的信息 |
| auth.log | 登录认证log |
| boot.log | 包含系统启动时的日志 |
| btmp | 记录所有失败启动信息 |
| Consolekit | 记录控制台信息 |
| cpus | 涉及所有打印信息的日志 |
| dist-upgrade | dist-upgrade这种更新方式的信息 |
| dmesg | 包含内核缓冲信息(kernel ringbuffer). 在系统启动时，显示屏幕上的与硬件有关的信息 |
| dpkg.log | 包括安装或dpkg命令清除软件包的日志 |
| faillog | 包含用户登录失败信息。此外，错误登录命令也会记录在本文件中 |
| fontconfig.log | 与字体配置有关的log |
| fsck | 文件系统日志 |
| faillog | 包含用户登录失败信息。此外，错误登录命令也会记录在本文件中 |
| kern.log | 包含内核产生的日志，有助于在定制内核时解决问题 |
| lastlog | 记录所有用户的最近信息。这不是一个ASCII文件，因此需要用lastlog命令查看内容 |
| faillog | 包含用户登录失败信息. 此外, 错误登录命令也会记录在本文件中 |
| mail | 这个子目录包含邮件服务器的额外日志 |
| mail.err | 类似于上面的 |
| samba | 包含由samba存储的信息 |
| wtmp | 包含登录信息。使用wtmp可以找出谁正在登陆进入系统，谁使用命令显示这个文件或信息等 |
| xorg.*.log | 来自X的日志信息 |

#2	没有 /var/log/messages和debug的解决方法
-------

```cpp
sudo vim /etc/rsyslog.d/50-default.conf
```

其中有这么一段

```cpp
#*.=info;*.=notice;*.=warn;\
#    auth,authpriv.none;\
#    cron,daemon.none;\
#    mail,news.none        -/var/log/messages
```

直接将所有#去掉即可，对于debug同理即可

```cpp
#*.debug;\
#         auth,authpriv.none;\
#         news.none;mail.none   -/var/log/debug
```

保存后重启rsylog服务

```cpp
sudo /etc/init.d/rsyslog restart
```

如果查看 文件夹 /var/log/ 内还没有 message.log 和debug.log ， 最好重启一下系统即可.


若无其他的log文件，同理以上方法处理即可在文件夹 /var/log 中找到。


<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作.
