#include "FastLED.h"

// constants to track which state the cube is currently in
volatile bool demoState = false;
volatile bool sonarState = true;
volatile bool micState = false;

#define STRIP_ONE_PIN 8
#define STRIP_TWO_PIN 9
#define STRIP_THREE_PIN 10
#define STRIP_FOUR_PIN 11

#define STRIP_LENGTH 32

#define LEDS_ON_TOP 10
#define LEDS_ON_SIDES 10
#define LEDS_ON_BOT 10

#define TAN 0     // pin 8
#define PURPLE 1  // pin 9 
#define PINK 2    // pin 10 
#define GREY 3    // pin 11

CRGB _rawleds[4][32];
int radius = 0;
#define DEMO_BUTTON 18  // correlates to interrupt 5
#define SONAR_BUTTON 19 // correlates to interrupt 4
#define MIC_BUTTON 20 // correlates to interrupt 3
// pin 8 tan
// pin 9 purple
// pin 10 pink
// pin 11 grey
void setup()
{
  Serial.begin(9600);
    FastLED.addLeds<NEOPIXEL, STRIP_ONE_PIN>(_rawleds[TAN], STRIP_LENGTH);
    FastLED.addLeds<NEOPIXEL, STRIP_TWO_PIN>(_rawleds[PURPLE], STRIP_LENGTH);
    FastLED.addLeds<NEOPIXEL, STRIP_THREE_PIN>(_rawleds[PINK], STRIP_LENGTH);
    FastLED.addLeds<NEOPIXEL, STRIP_FOUR_PIN>(_rawleds[GREY], STRIP_LENGTH);
   
    pinMode(18, INPUT);
    pinMode(19, INPUT);
    pinMode(20, INPUT);
    attachInterrupt(5, demo, CHANGE);
    attachInterrupt(4, sonar, CHANGE);
    attachInterrupt(3, mic, CHANGE);
}

void loop()
{
    spherePattern(radius);
    radius += (radius +1) % 40;
    if (demoState){
        // demo mode code
    }
    if (sonarState){
        // sonar mode code
    }
    if(micState){
        // mic/audio mode code
    }

}

void testCorners(){
  // pin 8 strip test
  getLED(1,0,0) =  CRGB::Blue;
  getLED(10,0,0) =  CRGB::Blue;
  getLED(11,1,0) = CRGB::Blue;
  getLED(11,10,0) = CRGB::Blue;
  getLED(11,11,1) = CRGB::Blue;
  getLED(11,11,10) = CRGB::Blue;
  //pin 9 
  getLED(11,0,1) = CRGB::Blue;
  getLED(11,0,10) = CRGB::Blue;
  getLED(11,1,11) = CRGB::Blue;
  getLED(11,10,11) = CRGB::Blue;
  getLED(1,11,11) = CRGB::Blue;
  getLED(10,11,11) = CRGB::Blue;
  //pin 10
  getLED(10,0,11) = CRGB::Blue;
  getLED(1,0,11) = CRGB::Blue;
  getLED(0,1,11) = CRGB::Blue;
  getLED(0,10,11) = CRGB::Blue;
  getLED(0,11,10) = CRGB::Blue;
  getLED(0,11,1) = CRGB::Blue;
  //pin 11
  getLED(0,0,1) = CRGB::Blue;
  getLED(0,0,10) = CRGB::Blue;
  getLED(0,1,0) = CRGB::Blue;
  getLED(0,10,0) = CRGB::Blue;
  getLED(1,11,0) = CRGB::Blue;
  getLED(10,11,0) = CRGB::Blue;
  FastLED.show();
}

void spherePattern(int r) {
  for(int x = 0; x < 12 ; x++) {for(int y = 0; y < 12 ; y++) {for(int z = 0; z < 12 ; z++) {
    if(inSphere(x,y,z,0,0,0,r)){
      if(!hasLED(x,y,z)) break;
      getLED(x,y,z) = CRGB::Red;
    }
    else {
      if(!hasLED(x,y,z)) break;
      getLED(x,y,z) = CRGB::Blue;
    }
  }}}
  FastLED.show();    
  FastLED.delay(20);
  
}

bool inSphere(int x, int y, int z, int cx, int cy, int cz, int r){
  return (pow(x - cx, 2) + pow(y - cy, 2) + pow(z - cz, 2)) < r && (pow(x - cx, 2) + pow(y - cy, 2) + pow(z - cz, 2)) > r-2;
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

void demo(){
    noInterrupts();
    demoState = true;
    sonarState = false;
    micState = true;
    interrupts();
}

void sonar(){
    noInterrupts();
    demoState = false;
    sonarState = true;
    micState = false;
    interrupts();
}

void mic(){
    noInterrupts();
    demoState = false;
    sonarState = false;
    micState = true;
    interrupts();
}
