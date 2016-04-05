#########################################################################
# File Name: yes_no_box.sh
# Author: gatieme
# Created Time: Tue 05 Apr 2016 03:57:33 PM CST
#########################################################################
#!/bin/bash






if (whiptail --title "Test Yes/No Box" --yesno "Choose between Yes and No." 10 60) then
        
    echo "You chose Yes. Exit status was $?."
    
else

    echo "You chose No. Exit status was $?."
    
fi



