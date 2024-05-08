#!/bin/bash

# JACK OPTIMISATION STUFF
#not running on pi zero raspbian lite
#sudo service ntp stop
#sudo service triggerhappy stop

# the below was hanging on pi4 bookworm
#sudo service dbus stop

#not running on pi zero raspbian lite
#sudo killall console-kit-daemon
#sudo killall polkitd
## Only needed when Jack2 is compiled with D-Bus support
#export DBUS_SESSION_BUS_ADDRESS=unix:path=/run/dbus/system_bus_socket


#sudo mount -o remount,size=128M /dev/shm

#killall gvfsd
#killall dbus-daemon
#killall dbus-launch

## Uncomment if you'd like to disable the network adapter completely
#echo -n "1-1.1:1.0" | sudo tee /sys/bus/usb/drivers/smsc95xx/unbind
#echo -n performance | sudo tee /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor

# get available soundcards using cat /proc/asound/cards
# edit the -dhw: command below as needed

sleep 5

#Running Jack at 22050khz
jackd -P70 -p16 -t2000 -d alsa -dhw:Device -p 128 -n 3 -r 44100 -s &

# leave enough time for jack to start before launching PD
sleep 10

MACADDRESS=$(cat /sys/class/net/wlan0/address)
echo "MAC: $MACADDRESS"

# PYTHON
sudo /home/pi/venv/bin/python /home/pi/enormousFM/scripts/helper.py $MACADDRESS &

# PUREDATA
pd -nogui -jack -open "/home/pi/enormousFM/pd/_MAIN.pd" -send "; RANDOM $RANDOM; " &

exit