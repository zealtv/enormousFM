# enormousFM
The Enormous Radio Project

![enormous node diagram](enormous-node.svg)


## puredata

Runs logic, audio duties, OSC.  Communicates to arduino via python helper.

## python

Provides admin services - updating, rebooting, shutdown.  Forwards OSC messages between arduino and puredata.

### Requires:
 - todo....


## Arduino

Reads distance sensor and controls lights and stepper motor.  Communicates with python via SLIP encoded OSC over serial USB.

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

## Install this repo
```
cd ~
git clone https://github.com/zealtv/enormousFM.git

```

## Configure soundcards
```
aplay -l
# determine soundcard name and edit start-jack.sh if required
# ie 
jackd -P70 -p16 -t2000 -d alsa -dhw:DigiAMP -p 128 -n 3 -r 22050 -s &

```


