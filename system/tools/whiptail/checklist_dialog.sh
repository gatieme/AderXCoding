#########################################################################
# File Name: checklist_dialog.sh
# Author: gatieme
# Created Time: Tue 05 Apr 2016 04:02:29 PM CST
#########################################################################
#!/bin/bash


#!/bin/bash
DISTROS=$(whiptail --title "Test Checklist Dialog" --radiolist \
    "What is the Linux distro of your choice?" 15 60 4 \
    "debian" "Venerable Debian" ON \
    "ubuntu" "Popular Ubuntu" OFF \
    "centos" "Stable CentOS" OFF \
    "mint" "Rising Star Mint" OFF 3>&1 1>&2 2>&3)

exitstatus=$?

if [ $exitstatus = 0 ]; then

    echo "The chosen distro is:" $DISTROS
    
else

    echo "You chose Cancel."
    
fi
