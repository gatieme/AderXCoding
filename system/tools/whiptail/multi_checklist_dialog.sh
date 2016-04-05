#########################################################################
# File Name: multi_checklist_dialog.sh
# Author: gatieme
# Created Time: Tue 05 Apr 2016 04:03:09 PM CST
#########################################################################
#!/bin/bash


DISTROS=$(whiptail --title "Test Checklist Dialog" --checklist \
    "Choose preferred Linux distros" 15 60 4 \
    "debian" "Venerable Debian" ON \
    "ubuntu" "Popular Ubuntu" OFF \
    "centos" "Stable CentOS" ON \
    "mint" "Rising Star Mint" OFF 3>&1 1>&2 2>&3)

exitstatus=$?

if [ $exitstatus = 0 ]; then

    echo "Your favorite distros are:" $DISTROS
    
else

    echo "You chose Cancel."
    
fi
