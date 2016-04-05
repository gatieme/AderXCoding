#########################################################################
# File Name: menu_dialog.sh
# Author: gatieme
# Created Time: Tue 05 Apr 2016 04:01:52 PM CST
#########################################################################
#!/bin/bash


#!/bin/bash
OPTION=$(whiptail --title "Test Menu Dialog" --menu "Choose your option" 15 60 4 \
    "1" "Grilled Spicy Sausage" \
    "2" "Grilled Halloumi Cheese" \
    "3" "Charcoaled Chicken Wings" \
    "4" "Fried Aubergine"  3>&1 1>&2 2>&3)

exitstatus=$?
if [ $exitstatus = 0 ]; then
 
    echo "Your chosen option:" $OPTION
    
else

    echo "You chose Cancel."
    
fi
