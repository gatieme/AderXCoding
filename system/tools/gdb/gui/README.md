GDB图形界面
=======

| CSDN | GitHub |
|:----:|:------:|
| [内核添加对yaffs2文件系统的支持](http://blog.csdn.net/gatieme/article/details/53157829) | [`AderXCoding/system/tools/yaffs2`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/yaffs2) |


<br>
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>
本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作
<br>

| 工具 | 描述 |
|：----：|：——---：|
| tui | gdb原生的图形模式，支持gdb所有的特性 |
| cgdb | 可以认为是TUI模式的增强版，具有代码高亮、查找等等功能。同时也支持gdb所有的特性。<br>
如果之前对gdb和vim比较熟悉的话，用这个就会很顺手 |
| ddd | 采用gdb作为后端，强大之处在于能够图形化显示程序中的结构体 |
| insight | |
| [Nemiver](https://github.com/GNOME/nemiver) | |
| [KDevelop](https://www.kdevelop.org/) | |

http://blog.csdn.net/shenyuflying/article/details/53931865
http://shenyu.wiki/2017/03/12/source-insight-color-theme/

| vim调试插件 | 描述 |
|：----：|：——---：|
vimgdb和clewn，pyclewn相对较少，gdbmgr
vgdb，pyclewn，VimDebug
https://www.lainme.com/doku.php/blog/2010/11/vim的调试插件_gdbmgr
http://blog.163.com/skyshore@126/blog/static/1339551362014828113227568/


gdb 插件
-------

http://www.freebuf.com/sectool/94235.html
http://www.cnblogs.com/0xmuhe/p/5627172.html
https://github.com/longld/peda
http://www.cjjjs.com/paper/czxt/20161215202120669.html


#KDbg
-------

http://www.kdbg.org


#Insight
-------

Insight是一个Tcl/Tk编写的gdb的图形用户接口，它是由在Red hat以及Cygnus的工程师写的。Red hat大方的将其捐赠给大众使用，甚至不时的提供人力继续完善它的功能。Insight项目始于1994年，至今已经颇为成熟，它能很好的发挥大部分gdb的强大功能。


target和host都是linux，一般很少GUI前端，不管是ddd还是insight，感觉都不如gdb自带的tui好用（在gdb的命令行模式下,ctrl+x+a 可以切换), 具体可以参考http://mingxinglai.com/cn/2013/07/gdbtui/;
http://wiki.ubuntu.org.cn/Insight的使用方法（gdb的最优前端）

#Affinic Debugger GUI
------

target如果是android的话，一般使用affinic debugger(www.affinic.com), 这个需要自己来配置remote debug的信息；

Affinic Debugger GUI For Linux 1.1.6

vi/vim使用进阶: 在VIM中使用GDB调试 – 使用vimgdb


xxgdb 是 gdb 的一个基于 X Window 系统的图形界面。 xxgdb 包括了命令行版的 gdb 上的所有特性。 xxgdb 使你能通过按按钮来执行常用的命令。 设置了断点的

cgdb

http://easwy.com/blog/archives/advanced-vim-skills-vim-gdb-vimgdb/

https://my.oschina.net/alphajay/blog/34509


<br>

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a>本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">知识共享署名-非商业性使用-相同方式共享 4.0 国际许可协议</a>进行许可, 转载请注明出处, 谢谢合作.


