# enormousFM

A Raspberry Pi and Arduino based framework for networked multichannel sound, light, and motion.  

![enormous node diagram](enormous-node.svg)


## puredata 0.54 vanilla 

Runs logic, audio duties, OSC.  Communicates to arduino via pd-comport.
Leverages the [bop](https://github.com/zealtv/bop) library. 

### Requires
- pd-comport


## python3

Provides admin services (updating, rebooting, shutdown). 

### Requires
- [pyOSC3](https://pypi.org/project/pyOSC3/)

## Arduino

Reads distance sensor and controls lights and stepper motor.  Communicates with PD via SLIP encoded OSC over USB serial.

### Requires:
- https://github.com/thomasfredericks/MicroOsc
- https://github.com/qub1750ul/Arduino_SharpIR
- http://www.airspayce.com/mikem/arduino/AccelStepper/
- https://github.com/FastLED/FastLED


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

# install pd externals
sudo apt-get install pd-comport

# add externals to local extra folder
mkdir ~/pd-externals
cd ~/pd-externals 
sudo cp /lib/pd/extra/* ./
sudo chown -R pi ./*

#install pip
sudo apt-get install pip

#make python virtual environment
cd ~
python3 -m venv ./venv

# install python dependencies
./venv/bin/pip install pyOSC3

```

## Install project code
```
# goto home directory
cd ~

# clone this repo (or your fork)
git clone https://github.com/zealtv/enormousFM.git

# !copy samples

# run update script 
sudo ~/enormousFM/scripts/update.sh

# pi should copy rc.local and reboot with jack, puredata, and helper.py running

```

# Arduino OSC schema
## from arduino
/d int  
IR sensor distance in centimeters


## to arduino
/leds float[10]  
brightness of LEDS 0.0 - 1.0

/ledsat float  
saturation of leds 0.0 - 1.0

/ledhue float  
hue of leds 0.0 - 1.0

/needle float  
needle speed