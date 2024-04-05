#!/bin/bash
sleep 15
jackd -P70 -p16 -t2000 -d alsa -dhw:CARD=DigiAMP -p 128 -n 3 -r 22050 -s &
sleep 5

pd -nogui -jack /home/pi/enormousFM/_MAIN.pd &
exit