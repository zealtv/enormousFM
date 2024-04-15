#include <MicroOscSlip.h>
#include <SharpIR.h>

// THE NUMBER 64 BETWEEN THE < > SYMBOLS  BELOW IS THE MAXIMUM NUMBER OF BYTES RESERVED FOR INCOMMING MESSAGES.
// MAKE SURE THIS NUMBER OF BYTES CAN HOLD THE SIZE OF THE MESSAGE YOUR ARE RECEIVING IN ARDUINO.
// OUTGOING MESSAGES ARE WRITTEN DIRECTLY TO THE OUTPUT AND DO NOT NEED ANY RESERVED BYTES.
MicroOscSlip<128> myMicroOsc(&Serial);  // CREATE AN INSTANCE OF MicroOsc FOR SLIP MESSAGES


SharpIR sensor( SharpIR::GP2Y0A21YK0F, A0 );


/********
  SETUP
*********/
void setup() {

  Serial.begin(115200);
}

/****************
  onReceiveOSC is triggered when a message is received
*****************/
void onReceiveOSC(MicroOscMessage& oscMessage) {

  // CHECK THE ADDRESS OF THE OSC MESSAGE
  //ECHO FSI
  if (oscMessage.checkOscAddressAndTypeTags("/echo", "fsi")) {

    float floatArgument = oscMessage.nextAsFloat();

    char stringArgument[20];
    const char* stringPointer = oscMessage.nextAsString();
    snprintf(stringArgument, 20, "%s", stringPointer);

    int intArgument = oscMessage.nextAsInt();

    myMicroOsc.sendMessage("/echo", "fsi", floatArgument, stringArgument, intArgument);
  }

  // if(oscMessage.checkOscAddressAndTypeTags("/getKnob", "i")){
  //   checkKnob();
  // }

  //LED MODE

  //NEEDLE POSITION


}

/*******
  LOOP
********/
void loop() {

  // TRIGGER onReceiveOSC() IF AN OSC MESSAGE IS RECEIVED :
  myMicroOsc.onOscMessageReceived(onReceiveOSC);

  checkDistance();

  // runExample();
}

void checkDistance(){
    static unsigned long myChronoStart;
    if (millis() - myChronoStart >= 50) {  // IF XX ms HAVE ELLAPSED
      myChronoStart = millis();            // RESTART CHRONO
      int32_t distance = sensor.getDistance();
      myMicroOsc.sendMessage("/d", "i", distance);
    }
}

// void checkKnob(){
//   knobPos = analogRead(knobPin);
//   if(knobPos != lastKnobPos){
//     myMicroOsc.sendMessage("/knob", "i", knobPos);
//   }
// }


void runExample(){
    // SEND OSC MESSAGES EVERY 20 MILLISECONDS :
  static unsigned long myChronoStart;
  if (millis() - myChronoStart >= 10) {  // IF XX ms HAVE ELLAPSED
    myChronoStart = millis();            // RESTART CHRONO

    float f_millis = float(millis()) / 1000.0;

    char s_millis[20];
    snprintf(s_millis, 20, "milliseconds:%ld", millis());

    // void sendMessage(const char *address, const char *format, ... );
    myMicroOsc.sendMessage("/stuff", "fsi", f_millis, s_millis, millis());

    // USE THE FOLLOWING METHODS TO SEND OSC MESSAGES :
    /*
      // SEND AN INT(32)
      myMicroOsc.sendInt(const char *address, int32_t i);
      // SEND A FLOAT
      myMicroOsc.sendFloat(const char *address, float f);
      // SEND A STRING
      myMicroOsc.endString(const char *address, const char *str);
      // SEND A BLOB
      myMicroOsc.sendBlob(const char *address, unsigned char *b, int32_t length);
      // SEND DOUBLE
      myMicroOsc.sendDouble(const char *address,double d);
      // SEND MIDI
      myMicroOsc.sendMidi(const char *address,unsigned char *midi);
      // SEND INT64
      myMicroOsc.sendInt64(const char *address, uint64_t h);
      // SEND A MIXED TYPE VARIABLE LENGTH MESSAGE
      myMicroOsc.sendMessage(const char *address, const char *format, ...);
    */
  }
}