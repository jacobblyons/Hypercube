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
    FastLED.addLeds<NEOPIXEL, 8>(_rawleds[0], 32);
    FastLED.addLeds<NEOPIXEL, STRIP_TWO_PIN>(_rawleds[1], STRIP_LENGTH);
    FastLED.addLeds<NEOPIXEL, STRIP_THREE_PIN>(_rawleds[2], STRIP_LENGTH);
    FastLED.addLeds<NEOPIXEL, STRIP_FOUR_PIN>(_rawleds[3], STRIP_LENGTH);
   
    pinMode(18, INPUT);
    pinMode(19, INPUT);
    pinMode(20, INPUT);
    attachInterrupt(5, demo, CHANGE);
    attachInterrupt(4, sonar, CHANGE);
    attachInterrupt(3, mic, CHANGE);
}

void loop()
{
  for(int i = 0 ; i < 32 ; i ++){
    getLED(9,i,0) = CRGB::Blue;
    delay(300);
    FastLED.show();
    
    getLED(9,i,0) = CRGB::Red;
    delay(300);
    FastLED.show();
  }
   
   
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
