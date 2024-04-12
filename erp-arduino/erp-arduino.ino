#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>
#include <SLIPEncodedSerial.h>

#ifdef BOARD_HAS_USB_SERIAL
SLIPEncodedUSBSerial SLIPSerial( thisBoardsSerialUSB );
#else
 SLIPEncodedSerial SLIPSerial(Serial); 
#endif

OSCErrorCode error;

int sensorPin = A0;   // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
int lastSensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  //begin SLIPSerial just like Serial
  SLIPSerial.begin(9600);   // set this as high as you can reliably run on your platform
}

void loop() {
    delay(25);

    OSCBundle bndl;
    int size;
    //receive a bundle
  while(!SLIPSerial.endofPacket())
    if( (size =SLIPSerial.available()) > 0)
    {
      while(size--)
        bndl.fill(SLIPSerial.read());
    }

  if(!bndl.hasError())
  {
    static int32_t sequencenumber=0;
    // we can sneak an addition onto the end of the bundle
    bndl.add("/micros").add((int32_t)micros()); // (int32_t) is the type of OSC Integers
    bndl.add("/sequencenumber").add(sequencenumber++);
    bndl.add("/digital/5").add(555.5);
    
    SLIPSerial.beginPacket(); // mark the beginning of the OSC Packet
        bndl.send(SLIPSerial);
    SLIPSerial.endPacket();     
  }
  else{
    // bndl.add("/micros").add((int32_t)micros());
    // SLIPSerial.beginPacket(); // mark the beginning of the OSC Packet
    // bndl.send(SLIPSerial);
    // SLIPSerial.endPacket();         
  }

  sensorValue = analogRead(sensorPin);
  if(sensorValue != lastSensorValue){
    bndl.add("/sensor").add(sensorValue);
    SLIPSerial.beginPacket(); // mark the beginning of the OSC Packet
    bndl.send(SLIPSerial);
    SLIPSerial.endPacket(); 
    lastSensorValue = sensorValue;
  }


}
