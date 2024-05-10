#!/bin/bash

# todo get samples from somewhere - ftp? scp? curl? wget?

cd /home/pi
# todo get samples.zip from somewhere - ftp? scp? curl? wget?

mkdir /home/pi/efm-temp
cd /home/pi/efm-temp
cp /home/pi/enormousFM/samples/README.md ./
cp /home/pi/enormousFM/samples/.gitignore ./
rm -rf /home/pi/enormousFM/samples
mkdir /home/pi/enormousFM/samples
unzip /home/pi/samples.zip -d /home/pi/enormousFM/samples
rm -r /home/pi/enormousFM/samples/__MACOSX
mv /home/pi/efm-temp/README.md /home/pi/enormousFM/samples/
mv /home/pi/efm-temp/.gitignore /home/pi/enormousFM/samples/
rm -r /home/pi/efm-temp
#set permissions
cd /home/pi/enormousFM/samples
chown -R pi ./

exit