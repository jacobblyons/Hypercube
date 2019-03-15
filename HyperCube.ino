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
volatile int sonarValue = 1;
volatile long times[2];
volatile long elapsed;
int count = 0;
bool newSig = true;
bool rec = false;
volatile int curPattern = 0;
int patternCount = 4;
volatile long lastPress;
const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
float lastLevel;
float audioLevel;
int dir = 1;
int tracerLength = 3;
int startIndex = 3;
int endIndex = 0;

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
    pinMode(A0, INPUT); // sonar sensor
    
    attachInterrupt(digitalPinToInterrupt(LEFT_BUTTON), toggleLeft, RISING);
    attachInterrupt(digitalPinToInterrupt(RIGHT_BUTTON), toggleRight,RISING);

    times[0] = 0;
    times[1] = 0;

}

void loop()
{
  //get sensor values 
//  int vval = analogRead(0);
//  int mm = vval*5;
//  int sonarInInches = mm/25.4;

  //Serial.println(sonarInInches );
//  risingFallingPattern(sonarInInches);
  //micpattern();
  //micPattern2();
//  playPattern1();
  runPattern();
//  risingFallingPattern(10);
//  sonarDistance(5);
//  exampleDemo(10);

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
    if(curPattern == 0){
      Serial.println("Entered case 0");
      risingFallingPattern();
      }
    else if(curPattern == 1){
      Serial.println("Entered case 1");
      risingFallingPattern();
    }
    else if(curPattern == 2){
      Serial.println("Entered case 2");
      micPattern2();
    }
    else if(curPattern == 3){
      Serial.println("Entered case 3");
      playPattern1();
    }
//  exampleDemo(200);
      
    }
      
//  switch(curPattern) {
//    case 0: 
//      risingFallingPattern(10);
//      Serial.println("Entered case 0");
//      break;
//    case 1 : 
//      pulsingPattern(20);  
//      Serial.println("Entered case 1");
//      break;
//    case 2 :
//       pulsingPattern(20);
//       Serial.println("Entered case 2");
//       break;
//    case 3: 
//      exampleDemo(20);
//      Serial.println("Entered case 3");
//      break;
  
//  }
//}


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

void micPattern(){
   double audio_volts = getAudioSignal();
//////////////////LED ASSIGNMENT///////////////////////////
//reset all leds back to black from last audio pass
//  for (int i = 10 ; i < STRIP_LENGTH; i ++) {
//    _rawleds[0][i] = CRGB::Black;
//    _rawleds[1][i] = CRGB::Black;
//    _rawleds[2][i] = CRGB::Black;
//    _rawleds[3][i] = CRGB::Black;
//    FastLED.show();
// }
    if(audio_volts < 2.2){      
    for (int i = 20 ; i < STRIP_LENGTH; i ++) {
      _rawleds[0][i] = CRGB::Black;
      _rawleds[1][i] = CRGB::Black;
      _rawleds[2][i] = CRGB::Black;
      _rawleds[3][i] = CRGB::Black;
      FastLED.show();
    }}
    if (audio_volts < 2.0){
      _rawleds[0][19] = CRGB::Black;
      _rawleds[1][19] = CRGB::Black;
      _rawleds[2][19] = CRGB::Black;
      _rawleds[3][19] = CRGB::Black;
      FastLED.show();
    }
    if (audio_volts < 1.8){
      _rawleds[0][18] = CRGB::Black;
      _rawleds[1][18] = CRGB::Black;
      _rawleds[2][18] = CRGB::Black;
      _rawleds[3][18] = CRGB::Black;
      FastLED.show();
    }
    if (audio_volts < 1.6){
      _rawleds[0][17] = CRGB::Black;
      _rawleds[1][17] = CRGB::Black;
      _rawleds[2][17] = CRGB::Black;
      _rawleds[3][17] = CRGB::Black;
      FastLED.show();
    }
    if (audio_volts < 1.4){
      _rawleds[0][16] = CRGB::Black;
      _rawleds[1][16] = CRGB::Black;
      _rawleds[2][16] = CRGB::Black;
      _rawleds[3][16] = CRGB::Black;
      FastLED.show();
    }
    if (audio_volts < 1.2){
      _rawleds[0][15] = CRGB::Black;
      _rawleds[1][15] = CRGB::Black;
      _rawleds[2][15] = CRGB::Black;
      _rawleds[3][15] = CRGB::Black;
      FastLED.show();
    }
    if (audio_volts < 1.0){
      _rawleds[0][14] = CRGB::Black;
      _rawleds[1][14] = CRGB::Black;
      _rawleds[2][14] = CRGB::Black;
      _rawleds[3][14] = CRGB::Black;
      FastLED.show();
    }
    if (audio_volts < 0.8){
      _rawleds[0][13] = CRGB::Black;
      _rawleds[1][13] = CRGB::Black;
      _rawleds[2][13] = CRGB::Black;
      _rawleds[3][13] = CRGB::Black;
      FastLED.show();
    }
    if (audio_volts < 0.7){
      _rawleds[0][12] = CRGB::Black;
      _rawleds[1][12] = CRGB::Black;
      _rawleds[2][12] = CRGB::Black;
      _rawleds[3][12] = CRGB::Black;
      FastLED.show();
    }
    if (audio_volts < 0.6){
      _rawleds[0][11] = CRGB::Black;
      _rawleds[1][11] = CRGB::Black;
      _rawleds[2][11] = CRGB::Black;
      _rawleds[3][11] = CRGB::Black;
      FastLED.show();
    }
    if (audio_volts < 0.4){
      _rawleds[0][10] = CRGB::Black;
      _rawleds[1][10] = CRGB::Black;
      _rawleds[2][10] = CRGB::Black;
      _rawleds[3][10] = CRGB::Black;
      FastLED.show();
    }

////max voltage ~= 2.4V, may need to scale adjustment based on mic tuning/gain,
    int scale = 9; //bottom strip always lit
    if (audio_volts <0.5){
      scale = 11;
    }
    if (audio_volts < 0.7&& audio_volts > 0.5){
      scale = 12; 
    }
    if (audio_volts < 1.0 && audio_volts > 0.7){
      scale = 13; 
    }
    if (audio_volts < 1.2 && audio_volts > 1.0){
     scale = 14;
    }
    if (audio_volts < 1.4 && audio_volts > 1.2){
     scale = 15;
    }
    if (audio_volts < 1.6 && audio_volts > 1.4){
      scale = 16; 
    }
    if (audio_volts < 1.8 && audio_volts > 1.6){
      scale = 17; 
    }
    if (audio_volts < 2.0 && audio_volts > 1.8){
     scale = 18;
    }
    if (audio_volts < 2.2 && audio_volts > 2.0){
     scale = 19;
    }
    if(audio_volts > 2.2){
      scale = STRIP_LENGTH;
    }
    
    for (int i = 0 ; i < scale; i ++) {
      if (i < 10){
        _rawleds[0][i] = CRGB::Green;
        _rawleds[1][i] = CRGB::Green;
        _rawleds[2][i] = CRGB::Green;
        _rawleds[3][i] = CRGB::Green;
      }
      if (i >= 10 && i <20){
        _rawleds[0][i] = CRGB::Yellow;
        _rawleds[1][i] = CRGB::Yellow;
        _rawleds[2][i] = CRGB::Yellow;
        _rawleds[3][i] = CRGB::Yellow;
      }
      if(i > 19){
        _rawleds[0][i] = CRGB::Red;
        _rawleds[1][i] = CRGB::Red;
        _rawleds[2][i] = CRGB::Red;
        _rawleds[3][i] = CRGB::Red;
      }
  }
  FastLED.show(); //display current levels
}

void micPattern2(){
   double audio_volts = getAudioSignal();
   if (dir == 1){
     for (int i = 0 ; i < STRIP_LENGTH; i ++) {
        if (i % 2 == 0){
          _rawleds[0][i] = CRGB::Gold;
          _rawleds[1][i] = CRGB::Gold;
          _rawleds[2][i] = CRGB::Gold;
          _rawleds[3][i] = CRGB::Gold;
        }else{
          _rawleds[0][i] = CRGB::Black;
          _rawleds[1][i] = CRGB::Black;
          _rawleds[2][i] = CRGB::Black;
          _rawleds[3][i] = CRGB::Black;
        }
    FastLED.show(); //display current levels 
    delay(20);
    }
    
     for (int i = 0 ; i < STRIP_LENGTH; i ++) {
        if (i % 2 != 0){
          _rawleds[0][i] = CRGB::Purple;
          _rawleds[1][i] = CRGB::Purple;
          _rawleds[2][i] = CRGB::Purple;
          _rawleds[3][i] = CRGB::Purple;
        }
      FastLED.show(); //display current levels 
      delay(20);
      }
    for (int i = 0 ; i < STRIP_LENGTH; i ++) {
        if (i % 2 == 0){
          _rawleds[0][i] = CRGB::Black;
          _rawleds[1][i] = CRGB::Black;
          _rawleds[2][i] = CRGB::Black;
          _rawleds[3][i] = CRGB::Black;
        }
    FastLED.show(); //display current levels 
    delay(20);
    }
      for (int i = 0 ; i < STRIP_LENGTH; i ++) {
      if (i % 2 != 0){
        _rawleds[0][i] = CRGB::Black;
        _rawleds[1][i] = CRGB::Black;
        _rawleds[2][i] = CRGB::Black;
        _rawleds[3][i] = CRGB::Black;
      }
    FastLED.show(); //display current levels 
    delay(20);
    } 
   }else{
     for (int i = STRIP_LENGTH-1 ; i >= 0; i--) {
        if (i % 2 == 0){
          _rawleds[0][i] = CRGB::Gold;
          _rawleds[1][i] = CRGB::Gold;
          _rawleds[2][i] = CRGB::Gold;
          _rawleds[3][i] = CRGB::Gold;
        }else{
          _rawleds[0][i] = CRGB::Purple;
          _rawleds[1][i] = CRGB::Purple;
          _rawleds[2][i] = CRGB::Purple;
          _rawleds[3][i] = CRGB::Purple;
        }
    FastLED.show(); //display current levels 
    delay(20);
    }
      for (int i = STRIP_LENGTH-1 ; i >= 0; i--) {
        if (i % 2 == 0){
          _rawleds[0][i] = CRGB::Black;
          _rawleds[1][i] = CRGB::Black;
          _rawleds[2][i] = CRGB::Black;
          _rawleds[3][i] = CRGB::Black;
        }else{
          _rawleds[0][i] = CRGB::Black;
          _rawleds[1][i] = CRGB::Black;
          _rawleds[2][i] = CRGB::Black;
          _rawleds[3][i] = CRGB::Black;
        }
    FastLED.show(); //display current levels 
    delay(20);
    } 
   }
   if (audio_volts > 1.4){
    dir *= -1;
   }
   Serial.println(audio_volts);
   Serial.println(dir);
}

void playPattern1(){  
  for (int i = endIndex ; i < startIndex; i++) {      
      _rawleds[0][i] = CRGB::DarkOrchid;
      FastLED.show();
  }
  for (int i = endIndex+tracerLength; i < startIndex + tracerLength; i++) {      
      _rawleds[0][i] = CRGB::Goldenrod;
      FastLED.show();

  }
  for (int i = endIndex - tracerLength - 2; i < startIndex+tracerLength+3;i++){// - tracerLength; i++){
    _rawleds[0][i] = CRGB::Black;
  }
  int sonarValue = (analogRead(0)*5)/25.4;
  delay(sonarValue);  //<--remove to inhibit seizure flashing
  endIndex++;
  startIndex++;
  if (endIndex > 121){
    endIndex = 0;}
  if (startIndex > 124){
    startIndex = 3;  
  }
}

double getAudioSignal(){
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level
   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;
 
   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(2);  //microphone on AnalogPin 2
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double audio_volts = (peakToPeak * 5.0) / 1024;  // convert to volts
   return audio_volts;
   //Serial.println(audio_volts);
}

void getDistance(){
  
}
