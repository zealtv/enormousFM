#!/bin/bash
cd /home/pi/enormousFM
echo "--- clearing changes"
git restore .
echo "--- pulling from git"
git pull
echo "--- updating submodules"
git submodule update --init --recursive
echo "--- setting permissions to allow PD write access"
chown -R pi ./
cd scripts
echo "--- copying rc.local"
sudo cp ./rc.local /etc/
echo "--- rebooting in 5 seconds..."
sleep 5
systemctl reboot