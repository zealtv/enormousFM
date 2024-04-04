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