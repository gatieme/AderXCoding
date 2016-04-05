#! /bin/sh
#写这个脚本原来是打算用来监测开发板上出现僵尸进程的状况，但是写好以后，
#发现在开发板上使用不是很靠谱，嵌入式linux系统使用的busybox中的命令都是精简的，
#很多通用选项不支持。但是还是能用的，当然在桌面系统上肯定是没问题的。 

#脚本功能：监测linux中不同运行状态的进程数目，及相应状态的具体进程 
#脚本用法：./cnt_zombie.sh   [运行平台:arm/pc]    [欲监测的进程运行状态: Z/R/S/SS/SW/T/...] 
#使用示例：./cnt_zombie.sh   arm  Z  ;    ./cnt_zombie.sh    pc   R ;

IFS_old=$IFS
IFS=$'\n'
file="zombie.txt"
num=0
proc_name=
self="cnt_zombie.sh"

while test true
do
    if [ $1 == "arm" ];
    then
        list="`ps -w|grep $2|grep -v grep|grep -v $self`"
    elif [ $1 == "pc" ];
    then
        list="`ps axu|grep -w $2|grep -v grep|grep -v $self`"
    fi

    if [ "x$list" != "x;" ]
    then
        x=
        #echo "list: $list"
        #num=`echo $list|wc -l`
        #echo "num: $num"
    else
        continue
    fi

    if [ $1 == "pc" ];
    then
        pos=`ps axu|grep PID|grep -bo COMMAND|cut -d ":" -f 1`
    elif [ $1 == "arm" ];
    then
        pos=26
    fi

    num=0
    for line in $list
    do
        num=$[$num+1]
        if [ -n $proc_name ];
        then
            proc_name="$proc_name\n\t`echo $line|cut -c $pos- `"
        else
            proc_name="`echo $line|cut -c $pos- `"
        fi
    done

    echo -e "process conut: $num, process list:$proc_name\n" >> $file
    sleep 3
done
