# enormousFM
## The Enormous Radio Project

A Raspberry Pi and Arduino based framework for networked multichannel sound, light, and motion using [Pure Data](https://puredata.info) and [bop](https://github.com/zealtv/bop). 

![enormous node diagram](enormous-node.svg)


## puredata 0.54 vanilla 

Runs logic, audio duties, OSC.  Communicates to arduino via python helper.

## python3

Provides admin services - updating, rebooting, shutdown. iInterfacing with arduino and OSC forwarding between arduino and puredata.

### Requires:
 - todo....


## Arduino

Reads distance sensor and controls lights and stepper motor.  Communicates with python via SLIP encoded OSC over USB serial.

### Requires:
- https://github.com/CNMAT/OSC


# Installation and Setup
## Flash SD using Raspberry Pi Imager
- Choose OS RASPBERRY PI OS LITE (64-BIT)
- Set username and password
- configure wireless LAN
- enable SSH
- Flash SD

## Install packages
```
# login
ssh pi@raspberrypi.local

# update
sudo apt-get update
sudo apt-get upgrade

# set gpu memory to 16 (if applicable)
sudo raspi-config

# install jack2
sudo apt-get install jackd2

# install git
sudo apt-get install git

# install pure-data dependencies
sudo apt-get install build-essential automake autoconf libtool gettext libasound2-dev libjack-jackd2-dev tcl tk wish

# install puredata 0.54+
cd ~
git clone https://github.com/pure-data/pure-data.git
cd ./pure-data/
./autogen.sh
./configure --enable-jack
make
sudo make install
```

## Install project code
```
# goto home directory
cd ~

# clone this repo
git clone https://github.com/zealtv/enormousFM.git

# goto scripts directory
cd ./enormousFM/scripts

# install rc.local autostart file and reboot
sudo ./update.sh

# pi should reboot with jack, python, and puredata running

```


