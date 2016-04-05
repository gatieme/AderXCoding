#########################################################################
# File Name: free_form_input_box.sh
# Author: gatieme
# Created Time: Tue 05 Apr 2016 03:59:45 PM CST
#########################################################################
#!/bin/bash


PET=$(whiptail --title "Test Free-form Input Box" --inputbox "What is your pet's name?" 10 60 Wigglebutt 3>&1 1>&2 2>&3)

exitstatus=$?
if [ $exitstatus = 0 ]; then

    echo "Your pet name is:" $PET
    
else

    echo "You chose Cancel."
    
fi
