Ubuntu 上安装开源系统备份软件 Systemback
=======

http://imcn.me/html/y2015/24421.html

http://bbs.kafan.cn/thread-1868695-1-1.html

http://www.linuxidc.com/Linux/2015-09/122560.htm

http://ubuntuhandbook.org/index.php/2014/07/install-backup-tool-systemback-1-0-ubuntu-14-04/

Systemback 是一款用于创建定点系统备份，使用户能够完全恢复操作系统的应用程序。提供了任何先进备份软件的功能，包括：系统备份、系统恢复、系统复制、系统安装、Live 系统创建、系统修复和系统升级


systemback_live_bios
从 Systemback 1.0版开始，Systemback 已经被移植到 QT5. 可用的最新版本是 Systemback 1.6.201，发布已经有一段时间了，有以下变化：

```cpp
Import new French and Russian translations
Exclude the not fstab-mounted filesystems in the /var/lib directory
Fix partitions unmounts when unmount a device
Fix systemback and systemback-cli manuals
Some optimizations
Lock the user input when deleting a Live image
Set ‘Back’ button focus after deleting a Live image
Add full screen installer mode for the Live systems
Add possibility to include user data files and directories into the restore points
Add possibility to exclude the directory content instead of the directory
Add support to GDM config file in Ubuntu
Move the configuration files into the ‘/etc/systemback’ directory
Remove all childrens when add a new item to the excluded list
Close the window if ‘OK’ button is clicked when the system copy is completed on the Live
Fix and shut up some error messages
Optimize CPU usage in some cases when executing external processes
Improve screen boundary check when moving or resizing the window
Do not start system upgrade in CLI without root permissions
Print error message when the systemback-cli is started on a Live system
Do not accept the scheduled restore point starting if the parent process is not the sbscheduler
Ignore the global font changes after the window is started
Fix segmentation faults in some keyPressEvents
Fix excluded items reading from file when the line start or end with space
Import new Hungarian and German translations
Remove Ubuntu 14.10 support
Add Ubuntu 15.10 packages to the Install Pack
```



安装说明：


到目前为止可以通过一些第三方PPA安装（支持 ubuntu 14.04/15.04/15.10），所以在Ubuntu上安装简直是小菜一碟。添加 PPA 到系统，更新本地存储库索引并安装systemback包：

```cpp
sudo add-apt-repository ppa:nemh/systemback
sudo apt-get update
sudo apt-get install systemback
```

卸载命令：
sudo apt-get remove systemback


![systemback]()


![systemback_live_uefi]()


>PPA 地址：https://launchpad.net/systemback
>
>下载地址：http://sourceforge.net/projects/systemback/