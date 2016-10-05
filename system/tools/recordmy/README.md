ubuntu下的录屏工具介绍
=======

>经本人试用, 觉得`recordmydesktop`最好用


#1	Istanbul
-------

Istanbul是目前比较广泛使用的录像软件之一.您可以点击这里下载Istanbul.DebianLINUX和FedoraLINUX的用户可以从repo(Fedora的主要更新源)安装改软件.Istanbul的操作界面非常简单,当您第一次启动Istanbul时,在系统桌面面板上会出现一个红色的圆形小按钮,如图1所示:


右键单击该按钮,会出现操作选单,如图2所示:


您可以选择录制窗口,或者是用鼠标选择录像区域,如果要停止录像,您可以左键单击该按钮,并且它会提示您保存所录得的文件,如图3,4所示:

提示:在默认情况下Istanbul会把截获的视频以OGG的格式存储.

#2	Wink
-------

相对于其他屏幕录像软件而言,Wink可以让您更精确的控制录像的过程,事实上,Wink的录像原理并不同于传统的屏幕录像软件,它是使用每秒钟屏 幕截图的帧数来达到录像的效果的,比如说你设定她每秒钟截取20帧,则一分钟下来,他就会连续的进行屏幕截图1200次左右,然后把这些截图按顺序排放, 构成视屏,这样以来,后期您可以通过修改其中的任何一帧来改变视频的外观.Wink通常把录制的文件保存为ShockWave格式,而这种格式的好处是, 可以被转换任何一种你想要的视频格式.

点击这里下载Wink

请注意Wink在以下情况下是不能工作的
—1.Ubuntu8.04以上的版本;
—2.其他在目录"/usr/lib/"中存在"libexpat.so.1"文件的LINUX发布版本,针对这种情况的解决方案是,重命名 "libexpat.so.0"这个文件,并且这样不会导致系统出现问题,当然了这种做法的缺陷是可能导致其他需要使用该文件的应用程序不能正常工作,一 个一劳永逸的的方案是重新编译受影响的应用程序,或者等待改程序更新版本的发布.

若要开始录像,则从"File"菜单的"New"选项开始,在弹出的对话框中选择录像的尺寸,如图5所示:

细心的你可能会发现,在默认情况下,Wink每秒钟会捕获50帧,如图6所示:


当您点击"OK"之后,会弹出一个窗口,其中有录制过程中所能用到的快捷键,如图7所示:

单击上图中的"MinimizeToTray",该操作将该程序最小化到系统托盘,相当于windows中的后台运行,右击系统托盘上的图标并选择"StartTimedCapture",就可以开始屏幕录像,如图8所示:

如果要停止录像,只需和开始录像一样,在弹出菜单中选择"StopTimedCapture",(在图8中显示为灰色不可用的菜单项),然后会生成录像报告,告诉您当前以捕获的帧数,如图9所示:


为了得到真正的视频文件,还要对所捕获的图像帧进行转换,具体操作见图10:(点击绿色的小箭头即可)

转换完成之后,进入保存文件对话框,在其中您可以自定义文件名,文件类型,帧频,如图11所示:

#3	Xvidcap
-------


Xvidcap是一款轻量型的屏幕录像软件,您可以点击这里下载该软件.启动Xvidcap之后,屏幕上会出现一个红色的矩形框,框内即为将要捕获的范围,当然您可以按照您的意愿随意拖动该框的位置可拖放其大小.开始录像的操作更是简单,只需点击图中的红色小按钮,如图12所示:

.<<其他的一些选项包括:自由选择捕获区域和使捕获区域和软件操作见面不重复>>

注意:如果您所选择的屏幕区域较大,他将会减慢系统的速度.

#4	vnc2swf
-------


另 一个比较流行但不太方便使用的屏幕录像软件叫做vnc2swf,他的工作原理是通过连接VNC服务器,捕获Session以获取录像, DebianLINUX的用户可以用命令"sudoapt-getinstallpyvnc2swf"安装该软件,其他用户则需到以下网站下载http://www.unixuser.org/~euske/vnc2swf/

软件安装完毕后,开始录像的操作仅仅是在"Terminal终端"输入"vnc2swf-otest.swf-N-Slocalhost:0",系统会出现录像的对话框,如图13所示:


更多的相关操作您可以查阅其官方文档.


#5	Recordmydesktop
-------


我 所要介绍的最后一款:Recordmydesktop也是被广泛使用的以命令行方式运行并且有图形化界面的屏幕录像软件,DebianLINUX 的用户可以用命令"sudoapt-getinstallrecordmydesktopgtk-recordmydesktop"安装该软件,其他用户 则需到以下网站下载http://sourceforge.net/projects/recordmydesktop

Recordmydesktop的工作方式和Istanbul很相似,但是他拥有一些Istanbul所没有的特性,并且这些特性具有很好的自我解释性,一般的用户很容易理解并进行相关配置,在这里不再赘述,其操作界面,如图14所示:


如果你不用linux，也不需要录像，这里还有在windows平台下的《截取图片的几个简单操作》。


#6	Kazam
-------

Kazam是Ubuntu 上一款简单并且功能强大的桌面屏幕录制工具，它能录制整个屏幕，可以录制声音，并可以快速上传录制好的视频到 YouTube 及 VideoBin 视频分享网站上。Kazam 目前最新版本为1.3.5，喜欢录屏的可以尝试下该款软件。

在Ubuntu 12.04,12.10 可通过PPA的方式安装该软件，打开终端执行如下命令：

sudo add-apt-repository ppa:kazam-team/unstable-series

Ubuntu 下安装桌面屏幕录制工具Kazam

sudo apt-get update && sudo apt-get install kazam

Ubuntu 下安装桌面屏幕录制工具Kazam

效果图如下：



#7	SimpleScreenRecorder
-------

https://www.sysgeek.cn/simplescreenrecorder-screen-recording-ubuntu/

大家可以在终端中使用如下命令安装 SimpleScreenRecorder


```cpp
sudo add-apt-repository ppa:maarten-baert/simplescreenrecorder
sudo apt-get update
sudo apt-get install simplescreenrecorder
```


如果你需要在 64 位 Ubuntu 上录制 32位 OpenGL 应用程序，请安装 simplescreenrecorder-lib:i386：

sudo apt-get install simplescreenrecorder-lib:i386
使用SimpleScreenRecorder

打开 SimpleScreenRecorder 时，你将看到如下界面：

SimpleScreenRecorder

点击「继续」按钮就会出现录制选项的配置界面，在此界面中大家可以按需配置视频的相关选项，如「录制整个屏幕」还是只「录制固定的区域」等。

SimpleScreenRecorder

在选项中大家可以看需要自行选择配置，并在确定好是否需要「录制光标」及配置好录音选项之后点击「继续」进行更多设置配置。

SimpleScreenRecorder

在上述步配置骤中，涉及到选择录屏文件的输出路径和视频容器。除常见视频格式外，SimpleScreenRecorder 还支持 Google 开源的 WebM 视频格式及 VP8 编解码器，非常不错。

SimpleScreenRecorder

快捷键应该是所有录屏软件的标配，SimpleScreenRecorder 自然也不例外。大家可以在这里配置快捷键并「开始预览」录制参数，在所有内容都确认无误之后即可「开始录制」。录制完成之后，大家只需点击「保存录像」即可完成所有操作。


#8	Tibesti
-------


```cpp
sudo add-apt-repository ppa:ackondro/tibesti
sudo apt-get update
sudo apt-get install tibesti
```

http://www.startos.com/ubuntu/tips/2010122116689.html


#9	Vokoscreen
-------

http://www.mintos.org/skill/vokoscreen-capture.html


今天介绍的主角是`Vokoscreen`, 与 Kazam 旗鼓相当的屏幕录制软件。先看看 开源中国 的介绍：
vokoscreen 是一个易用开源的屏幕录像软件，一般用来录制教育用的视频。主要特性：
易用的图形化界面
可记录全屏、单独某个窗口和某个指定区域
放大: 200x200, 400x200, 600x200
缩放
同步捕获摄像头
点击进行录制
支持视频编码：mpeg4 和 libx265
格式支持 mkv 和 avi
支持不记录鼠标指针
支持热键
自动隐藏的特性，通过任务栏进行控制
支持国际化
据新近消息，Vokoscreen 已经加入到 Ubuntu 14.04 软件源，使用 Ubuntu 14.04/Linux Mint 17 的用户可以直接在“软件中心”（软件管理器）中搜索安装。对于 Ubuntu 12.04-13.10 的用户，则使用如下 PPA 安装：
sudo add-apt-repository ppa:vokoscreen-dev/vokoscreen
sudo apt-get update
sudo apt-get install vokoscreen
还魂草直接在“软件源”设置中添加 PPA：
