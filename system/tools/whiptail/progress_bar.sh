#########################################################################
# File Name: progress_bar.sh
# Author: gatieme
# Created Time: Tue 05 Apr 2016 03:55:51 PM CST
#########################################################################
#!/bin/bash


#Progress bar
{
 
    for ((i = 0 ; i <= 100 ; i+=20)); do
    
        sleep 1        
        echo $i
        
    done
    
} | whiptail --gauge "Please wait while installing" 6 60 0
