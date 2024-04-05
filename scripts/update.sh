#!/bin/bash
cd /home/pi/enormousFM
echo "stashing changes"
git stash
echo "pulling from git"
git pull
echo "updating submodules"
git submodule update --init --recursive
cd scripts
echo "copying rc.local"
./copyrc.sh
echo "rebooting in 5 seconds..."
sleep 5
systemctl reboot