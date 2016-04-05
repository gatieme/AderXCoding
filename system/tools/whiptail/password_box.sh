#########################################################################
# File Name: password_box.sh
# Author: gatieme
# Created Time: Tue 05 Apr 2016 04:00:28 PM CST
#########################################################################
#!/bin/bash


#!/bin/bash
PASSWORD=$(whiptail --title "Test Password Box" --passwordbox "Enter your password and choose Ok to continue." 10 60 3>&1 1>&2 2>&3)

exitstatus=$?
if [ $exitstatus = 0 ]; then

    echo "Your password is:" $PASSWORD

else
    
    echo "You chose Cancel."
    
fi
