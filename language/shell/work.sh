#  mount the  192.168.10.133
#  实验室的两个节点
#  192.168.10.133 可以上网并且安装了git
#  但是192.168.18.10 不能上网
#  因此为192.168.18.10 配置了eth0:0的IP = 192.168.10.254
#
#
#  此脚本用于共享工作目录，
#  将192.168.10.133:/home/gatieme/Work共享到了192.168.18.10
ping -c 1 -w 5 192.168.10.133

if [ $? != 0 ];then
    echo "can't connect the 192.168.10.133..."
else 
    echo "can conenct 192.168.10.133"
    
    if [ $1 == "start" ];then
        sudo mount -o tcp,nolock 192.168.10.133:/home/gatieme/Work /home/gatieme/Work
        echo "mount the 192.168.10.133:/home/gatieme"
    elif [ $1 == "stop" ];then
        sudo umount /home/gatieme/Work
        echo "umount the 192.168.10.133:/home/gatieme"
    fi
fi
