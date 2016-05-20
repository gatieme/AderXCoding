#########################################################################
# File Name: getppid.sh
# Author: gatieme
# Created Time: Fri 20 May 2016 03:17:55 PM CST
#########################################################################
#!/bin/bash

#通过ps -p pid -o 来输出进程的父亲进程信息

pid=$1
if [ -z $pid ];then
    read -p "PID: " pid
fi 
    ps -p ${pid:-$$} -o ppid=
