#!/bin/bash

gcc server-bmi.c -o serverbmi
gcc client-bmi.c -o clientbmi


gnome-terminal -- bash -c "./serverbmi"

 
sleep 2


gnome-terminal -- bash -c "./clientbmi"


read -p "Press Enter to exit..."
