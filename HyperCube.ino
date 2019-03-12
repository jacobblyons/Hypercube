#include "FastLED.h"


#define STRIP_ONE_PIN 8
#define STRIP_TWO_PIN 10
#define STRIP_THREE_PIN 11
#define STRIP_FOUR_PIN 9
#define STRIP_LENGTH 32
#define LEDS_ON_TOP 10
#define LEDS_ON_SIDES 10
#define LEDS_ON_BOT 10
#define TAN 0     // pin 8
#define PURPLE 1  // pin 9 
#define PINK 2    // pin 10 
#define GREY 3    // pin 11

// constants to track which state the cube is currently in
volatile bool demoState = false;
volatile bool sonarState = false;
volatile bool micState = false;
volatile long times[2];
volatile long elapsed;
int count = 0;
bool newSig = true;
bool rec = false;
volatile int curPattern = 0;
int patternCount = 12;
volatile long lastPress;

CRGB _rawleds[4][32];

#define LEFT_BUTTON 18 
#define RIGHT_BUTTON 19 


// pin 8 tan
// pin 9 purple
// pin 10 pink
// pin 11 grey
void setup()
{
    Serial.begin(9600);
    lastPress = micros();
    FastLED.addLeds<NEOPIXEL, STRIP_ONE_PIN>(_rawleds[TAN], STRIP_LENGTH);
    FastLED.addLeds<NEOPIXEL, STRIP_TWO_PIN>(_rawleds[PURPLE], STRIP_LENGTH);
    FastLED.addLeds<NEOPIXEL, STRIP_THREE_PIN>(_rawleds[PINK], STRIP_LENGTH);
    FastLED.addLeds<NEOPIXEL, STRIP_FOUR_PIN>(_rawleds[GREY], STRIP_LENGTH);
   
    pinMode(LEFT_BUTTON, INPUT);
    pinMode(RIGHT_BUTTON, INPUT);
    
    attachInterrupt(digitalPinToInterrupt(LEFT_BUTTON), toggleLeft, RISING);
    attachInterrupt(digitalPinToInterrupt(RIGHT_BUTTON), toggleRight,RISING);

    times[0] = 0;
    times[1] = 0;
}

void loop()
{
    runPattern();
    

}

void toggleLeft(){
    noInterrupts();
    if(micros() - lastPress < 170000) return;
    curPattern = curPattern == 0 ? patternCount -1 : curPattern -1;
    Serial.println(curPattern);
    lastPress = micros();
    interrupts();
}

void toggleRight() {
  noInterrupts();
  if(micros() - lastPress < 150000) return;
  curPattern = (curPattern +1) % patternCount;
  Serial.println(curPattern);
  lastPress = micros();
  interrupts();
}

void runPattern() {
  switch(curPattern) {
    case 0: 
      risingFallingPattern();
      break;
    case 1 : 
      pulsingPattern(20);  
      break;
    case 2 :
       pulsingPattern(20);
       break;
  }
}


void testCorners(){
  // pin 8 strip test
  getLED(1,0,0) =  CRGB::Green;
  getLED(10,0,0) =  CRGB::Green;
  getLED(11,1,0) = CRGB::Green;
  getLED(11,10,0) = CRGB::Green;
  getLED(11,11,1) = CRGB::Green;
  getLED(11,11,10) = CRGB::Green;
  //pin 9 
  getLED(11,0,1) = CRGB::Red;
  getLED(11,0,10) = CRGB::Red;
  getLED(11,1,11) = CRGB::Red;
  getLED(11,10,11) = CRGB::Red;
  getLED(1,11,11) = CRGB::Red;
  getLED(10,11,11) = CRGB::Red;
  //pin 10
  getLED(10,0,11) = CRGB::Yellow;
  getLED(1,0,11) = CRGB::Yellow;
  getLED(0,1,11) = CRGB::Yellow;
  getLED(0,10,11) = CRGB::Yellow;
  getLED(0,11,10) = CRGB::Yellow;
  getLED(0,11,1) = CRGB::Yellow;
  //pin 11
  getLED(0,0,1) = CRGB::Blue;
  getLED(0,0,10) = CRGB::Blue;
  getLED(0,1,0) = CRGB::Blue;
  getLED(0,10,0) = CRGB::Blue;
  getLED(1,11,0) = CRGB::Blue;
  getLED(10,11,0) = CRGB::Blue;
  FastLED.show();
}


void testAll(){
  int delayTime = 15;
  for (int i = 0 ; i < STRIP_LENGTH; i ++) {
    _rawleds[0][i] = CRGB::Red;
    FastLED.show();

    _rawleds[0][i] = CRGB::Red;
    FastLED.show();

  }
  for (int i = 0 ; i < STRIP_LENGTH; i ++) {
    _rawleds[1][i] = CRGB::Red;
    FastLED.show();

    _rawleds[1][i] = CRGB::Red;
    FastLED.show();
 
  }
  for (int i = 0 ; i < STRIP_LENGTH; i ++) {
    _rawleds[2][i] = CRGB::Red;
    FastLED.show();

    _rawleds[2][i] = CRGB::Red;
    FastLED.show();

  }
  for (int i = 0 ; i < STRIP_LENGTH; i ++) {
    _rawleds[3][i] = CRGB::Red;
    FastLED.show();
 
    _rawleds[3][i] = CRGB::Red;
    FastLED.show();

  }
}


void ECHOR(){
  noInterrupts();
  count++;
  if (count > 10){
    rec = true;
    //Serial.println('R');
    times[0] = micros();
    count = 0;
  }  
  interrupts();
}

void ECHOF(){
  noInterrupts();
  //Serial.println('F');
  if (rec){
    times[1] = micros();
    newSig = true;
    rec = false;
  }
  interrupts();
}

void getDistance(){
  
}
