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

#define LEDS_ON_TOP 11
#define LEDS_ON_SIDES 11
#define LEDS_ON_BOT 10

#define TAN 0
#define PURPLE 1
#define PINK 2
#define GREY 3

CRGB _rawleds[4][32];

#define DEMO_BUTTON 18  // correlates to interrupt 5
#define SONAR_BUTTON 19 // correlates to interrupt 4
#define MIC_BUTTON 20 // correlates to interrupt 3

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
  
  testx();
   
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
void testx() {
  int delayTime = 100;
  for(int i = 0 ; i < LEDS_ON_BOT ; i ++){
    //bot right
    getLED(i,0,0) = CRGB::Blue;
    delay(delayTime);
    FastLED.show();
    getLED(i,0,0) = CRGB::Red;
    delay(delayTime);
    FastLED.show();

    //botleft
    getLED(i,0,LEDS_ON_BOT-1) = CRGB::Blue;
    delay(delayTime);
    FastLED.show();
    getLED(i,0,LEDS_ON_BOT-1) = CRGB::Red;
    delay(delayTime);
    FastLED.show();
    
    //topright DEAD LEDS
    getLED(i,LEDS_ON_SIDES -1,0) = CRGB::Blue;
    delay(delayTime);
    FastLED.show();
    getLED(i,LEDS_ON_SIDES -1,0) = CRGB::Red;
    delay(delayTime);
    FastLED.show();

    //topleft
    getLED(i,LEDS_ON_SIDES -1,LEDS_ON_TOP -1) = CRGB::Blue;
    delay(delayTime);
    FastLED.show();
    getLED(i,LEDS_ON_SIDES -1,LEDS_ON_TOP -1) = CRGB::Red;
    delay(delayTime);
    FastLED.show();
  }
}

void testAll(){
  int delayTime = 15;
  for (int i = 0 ; i < STRIP_LENGTH; i ++) {
    _rawleds[0][i] = CRGB::HotPink;
    FastLED.show();
    delay(delayTime);
    _rawleds[0][i] = CRGB::HotPink;
    FastLED.show();
    delay(delayTime);
  }
  for (int i = 0 ; i < STRIP_LENGTH; i ++) {
    _rawleds[1][i] = CRGB::HotPink;
    FastLED.show();
    delay(delayTime);
    _rawleds[1][i] = CRGB::HotPink;
    FastLED.show();
    delay(delayTime);
  }
  for (int i = 0 ; i < STRIP_LENGTH; i ++) {
    _rawleds[2][i] = CRGB::HotPink;
    FastLED.show();
    delay(delayTime);
    _rawleds[2][i] = CRGB::HotPink;
    FastLED.show();
    delay(delayTime);
  }
  for (int i = 0 ; i < STRIP_LENGTH; i ++) {
    _rawleds[3][i] = CRGB::HotPink;
    FastLED.show();
    delay(delayTime);
    _rawleds[3][i] = CRGB::HotPink;
    FastLED.show();
    delay(delayTime);
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
