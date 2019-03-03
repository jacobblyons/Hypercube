#include "LEDCube.h"
#include "Arduino.h"

#define STRIP_ONE_PIN 8
#define STRIP_TWO_PIN 9
#define STRIP_THREE_PIN 10
#define STRIP_FOUR_PIN 11

#define STRIP_ONE_LENGTH 30
#define STRIP_TWO_LENGTH 30
#define STRIP_THREE_LENGTH 33
#define STRIP_FOUR_LENGTH 33
#define LEDS_ON_TOP 11
#define LEDS_ON_SIDES 11
#define LEDS_ON_BOT 10

#define X_LENGTH 10
#define Y_LENGTH 10
#define Z_LENGTH 10

#define TAN 0
#define PURPLE 0
#define PINK 0
#define GREY 0

LEDCube::LEDCube()
{
    FastLED.addLeds<NEOPIXEL, STRIP_ONE_PIN>(_rawleds[0], STRIP_ONE_LENGTH);
    FastLED.addLeds<NEOPIXEL, STRIP_ONE_PIN>(_rawleds[1], STRIP_TWO_LENGTH);
    FastLED.addLeds<NEOPIXEL, STRIP_ONE_PIN>(_rawleds[2], STRIP_THREE_LENGTH);
    FastLED.addLeds<NEOPIXEL, STRIP_ONE_PIN>(_rawleds[3], STRIP_FOUR_LENGTH);

    //init the 3d array
    for (int x = 0; x < X_LENGTH; x++)
    {
        for (int y = 0; y < Y_LENGTH; y++)
        {
            for (int z = 0; z < Y_LENGTH; z++)
            {
                _ledMatrix[x][y][z] = NULL;
            }
        }
    }

    //painfully hardcoded edges
    //using the model:
    //  tan is strip 1
    //  purple is strip 2
    //  pink is strip 3
    //  grey is strip 4
    for (int x = 0; x < X_LENGTH; x++)
    {
        _ledMatrix[x][Y_LENGTH][Z_LENGTH] = _rawleds[PURPLE][STRIP_THREE_LENGTH - 1 - x]; //top left
        _ledMatrix[x][Y_LENGTH][0] = _rawleds[GREY][LEDS_ON_BOT + LEDS_ON_SIDES - 1 + x]; //top right
        _ledMatrix[x][0][Z_LENGTH] = _rawleds[PINK][LEDS_ON_BOT - 1 - x];                 //bot left
        _ledMatrix[x][0][0] = _rawleds[TAN][x];                                           //bot right
    }

    for (int y = 0; y < Y_LENGTH; y++)
    {
        _ledMatrix[0][y][0] = _rawleds[GREY][LEDS_ON_BOT - 1 + y];                 //top left
        _ledMatrix[X_LENGTH][y][0] = _rawleds[TAN][LEDS_ON_BOT - 1 + y];           //top right
        _ledMatrix[0][y][Z_LENGTH] = _rawleds[PINK][LEDS_ON_BOT - 1 + y];          //bot left
        _ledMatrix[X_LENGTH][y][Z_LENGTH] = _rawleds[PURPLE][LEDS_ON_BOT - 1 + y]; //bot right
    }

    for (int z = 0; z < Z_LENGTH; z++)
    {
        _ledMatrix[0][Y_LENGTH][z] = _rawleds[PINK][STRIP_THREE_LENGTH - 1 - z];                //top left
        _ledMatrix[X_LENGTH][Y_LENGTH][z] = _rawleds[TAN][LEDS_ON_BOT + LEDS_ON_SIDES - 1 + z]; //top right
        _ledMatrix[0][0][z] = _rawleds[GREY][LEDS_ON_BOT - 1 - z];                              //bot left
        _ledMatrix[X_LENGTH][0][z] = _rawleds[PURPLE][z];                                       //bot right
    }
}

CRGB &LEDCube::getLED(int x, int y, int z)
{
    return _ledMatrix[x][y][z];
}

int LEDCube::size()
{
    return FastLED.size();
}

CFastLED &LEDCube::getController()
{
    return FastLED;
}
