Ubuntu14.04升级vim7.4到8.0
=======

| CSDN | GitHub |
|:----:|:------:|
| [Ubuntu14.04升级vim7.4到8.0](http://blog.csdn.net/gatieme/article/details/52752070) | [`AderXCoding/system/tools/vim`](https://github.com/gatieme/AderXCoding/tree/master/system/tools/vim) |


将VIM配置为默认多标签打开

gvim能否只开一个窗口，每次在终端“gvim 文件名”的时候就自动在这个窗口新开一个tab page来打开文件？ 这样桌面简洁很多，就像windows下用UltraEdit一样。可以在gvim中用:tabnew :e，但太麻烦了。 

这样做： 
gvim   --remote-tab-silent  filename 

linux下 
为了方便可以在.bashrc中加入 
alias vim='gvim --remote-tab-silent' 
alias gvim='gvim --remote-tab-silent' 

windows 下要分2步：

*	双击时打开标签页

修改注表

```cpp
/HKEY_CLASSES_ROOT/Applications/gvim.exe/shell/edit/command
```
的值

```cpp
"F:\SoftwareEngineer\Vim\vim80\gvim.exe" "%1"
```

为

```cpp
"F:\SoftwareEngineer\Vim\vim80\gvim.exe" -p --remote-tab-silent "%1"
```


*	鼠标右键时打开标签页

打开注册表，添加以下项： 
            [HKEY_CLASSES_ROOT\*\]下添加Shell项　　　　　　
            [HKEY_CLASSES_ROOT\*\Shell] 下添加Edit with &Vim项
            [HKEY_CLASSES_ROOT\*\Shell\Edit with &Vim] 添加command项
            [HKEY_CLASSES_ROOT\*\Shell\Edit with &Vim\command]修改默认值为"D:\Program Files\Vim\vim73\gvim.exe" -p --remote-tab-silent "%1"
退出注册表，右键显示Edit with Vim

https://wangheng.org/html/edit_with_vim.html

http://www.cppblog.com/lateCpp/articles/151240.html
