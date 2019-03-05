#include <LEDCube.h>

LEDCube c;

// constants to track which state the cube is currently in
volatile bool demoState = false;
volatile bool sonarState = true;
volatile bool micState = false;

#define DEMO_BUTTON 18  // correlates to interrupt 5
#define SONAR_BUTTON 19 // correlates to interrupt 4
#define MIC_BUTTON 20 // correlates to interrupt 3

void setup()
{
   c = LEDCube();
   c.getController();
   c.getLED(0,0,0).setRGB(255,255,20);
    pinMode(18, INPUT);
    pinMode(19, INPUT);
    pinMode(20, INPUT);
    attachInterrupt(5, demo, CHANGE);
    attachInterrupt(4, sonar, CHANGE);
    attachInterrupt(3, mic, CHANGE);
}

void loop()
{
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
