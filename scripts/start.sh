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
jackd -P70 -p16 -t2000 -d alsa -dhw:DigiAMP -p 128 -n 3 -r 22050 -s &

# leave enough time for jack to start before launching PD
sleep 5

# PYTHON
# todo

# PUREDATA
MACADDRESS=$(cat /sys/class/net/wlan0/address | tr ':' ' ')
now=$(date --iso-8601=seconds)
STARTDATE=$(date -d "$now" +%Y%m%d)
STARTTIME=$(date -d "$now" +%H%M%S)

echo "MAC: $MACADDRESS"

pd -nogui -jack -open "/home/pi/enormousFM/_MAIN.pd" -send "; STARTTIME $STARTTIME; RANDOM $RANDOM; MACADDRESS $MACADDRESS" &

exit