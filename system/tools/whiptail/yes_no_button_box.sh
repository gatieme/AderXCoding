#########################################################################
# File Name: yes_no_button_box.sh
# Author: gatieme
# Created Time: Tue 05 Apr 2016 03:58:42 PM CST
#########################################################################
#!/bin/bash


#!/bin/bash
if (whiptail --title "Test Yes/No Box" --yes-button "Skittles" --no-button "M&M's"  --yesno "Which do you like better?" 10 60) then
        
    echo "You chose Skittles Exit status was $?."
    
else

    echo "You chose M&M's. Exit status was $?."
    
fi
