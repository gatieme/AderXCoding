#!/bin/bash



#---------------------
#
#   更新系统
#
#---------------------
if (whiptail --title "Would like to upgrade you system now" \
    --yesno "Choose between Yes and No." 10 60) then
    echo "Start upgrade your system"
    sudo apt-get update
    sudo apt-get dist-upgrade
else
    echo "System will not dist-upgrade"
fi




#---------------------
#
#   安装系统
#
#---------------------
DISTROS=$(whiptail --title "Test Checklist Dialog" --checklist \
    "Choose preferred Linux distros" 15 60 4 \
    "numix-icon" "Numix Icon Theme" ON \
    "ubuntu-tweak" "Ubuntu Tweak Tools" OFF \
    "centos" "Stable CentOS" ON \
    "mint" "Rising Star Mint" OFF 3>&1 1>&2 2>&3)

exitstatus=$?
if [ $exitstatus = 0 ]; then
    echo "Your favorite distros are:" $DISTROS
else
    echo "You chose Cancel."
fi

for i in $DISTROS
do
    sudo apt-get install $i
done
