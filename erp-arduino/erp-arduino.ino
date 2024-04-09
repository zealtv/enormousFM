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

void setup() {
  //begin SLIPSerial just like Serial
  SLIPSerial.begin(9600);   // set this as high as you can reliably run on your platform
}

void loop() {
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
}
