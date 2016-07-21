https://github.com/2225377fjs/processNet
git@github.com:2225377fjs/processNet.git

一个用于在linux下面获取进程网络带宽的python扩展库，用c++以及libcap开发

现在是离线的版本。。。

用法：
import fjs

首先加入要监控的进程PID，如下：
fjs.addProcess(pid)

获取流量的信息：
fjs.getInfoByPid(pid)
