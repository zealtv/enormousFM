#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Stepper.h>
#include <MicroOscSlip.h>
#include <SharpIR.h>
#include <FastLED.h>

//LEDs
#define NUM_LEDS 10
#define DATA_PIN 3
CRGB leds[NUM_LEDS];
int ledSaturation = 0;
int ledHue = 0;

//MOTOR
// Motor pin definitions:
#define motorPin1  9     // IN1 on the ULN2003 driver
#define motorPin2  10     // IN2 on the ULN2003 driver
#define motorPin3  11     // IN3 on the ULN2003 driver
#define motorPin4  12     // IN4 on the ULN2003 driver
AccelStepper stepper = AccelStepper(AccelStepper::FULL4WIRE, motorPin1, motorPin3, motorPin2, motorPin4);

// THE NUMBER 64 BETWEEN THE < > SYMBOLS  BELOW IS THE MAXIMUM NUMBER OF BYTES RESERVED FOR INCOMMING MESSAGES.
// MAKE SURE THIS NUMBER OF BYTES CAN HOLD THE SIZE OF THE MESSAGE YOUR ARE RECEIVING IN ARDUINO.
// OUTGOING MESSAGES ARE WRITTEN DIRECTLY TO THE OUTPUT AND DO NOT NEED ANY RESERVED BYTES.
MicroOscSlip<128> myMicroOsc(&Serial);  // CREATE AN INSTANCE OF MicroOsc FOR SLIP MESSAGES

//IR SENSOR
SharpIR sensor( SharpIR::GP2Y0A21YK0F, A0 );


/********
  SETUP
*********/
void setup() {
  Serial.begin(115200);
  
  // Set the maximum steps per second:
  stepper.setMaxSpeed(1000);

  //set up LEDs
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(84);
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


  //NEEDLE POSITION
  if(oscMessage.checkOscAddressAndTypeTags("/needle", "f")){
    float needlePos = oscMessage.nextAsFloat();
    setNeedle(needlePos);
  }


  //LEDS
  //number of args must be the same as NUM_LEDS
  if(oscMessage.checkOscAddressAndTypeTags("/leds", "ffffffffff")){
    for(int i = 0; i < NUM_LEDS; i++){
      int brightness = (int)(oscMessage.nextAsFloat() * 255);
      leds[i] = CHSV(ledHue, ledSaturation, brightness);
      FastLED.show();
    }
  }

  if(oscMessage.checkOscAddressAndTypeTags("/ledsat", "f")){
    ledSaturation = (int)(oscMessage.nextAsFloat() * 255);
  }
  
  if(oscMessage.checkOscAddressAndTypeTags("/ledhue", "f")){
    ledHue = (int)(oscMessage.nextAsFloat() * 255);
  }
}

/*******
  LOOP
********/
void loop() {

  // TRIGGER onReceiveOSC() IF AN OSC MESSAGE IS RECEIVED :
  myMicroOsc.onOscMessageReceived(onReceiveOSC);

  checkDistance();
  stepper.runSpeed();
  // runExample();
}

void checkDistance(){
    static unsigned long myChronoStart;
    static int32_t lastDistance;
    if (millis() - myChronoStart >= 50) {  // IF XX ms HAVE ELLAPSED
      myChronoStart = millis();            // RESTART CHRONO
      int32_t distance = sensor.getDistance();
      if(distance != lastDistance)
        myMicroOsc.sendMessage("/d", "i", distance);
      lastDistance = distance;
    }
}


void setNeedle(float needlePos){
  stepper.setSpeed((int)needlePos);
  
  if(needlePos == 0)
    stepper.disableOutputs(); 
  else
    stepper.enableOutputs(); 
    
}







//----------------- TEST LOOP
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



