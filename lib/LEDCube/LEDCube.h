#ifndef LEDCube_h
#define LEDCube_h

#include "Arduino.h"
#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <FastLED.h>
#include <fastpin.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <fastspi.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

#define X_LENGTH 10
#define Y_LENGTH 10
#define Z_LENGTH 10
#define LED_STRIP_COUNT 4
#define MAX_LED_LENGTH 11

class LEDCube
{
public:
  LEDCube();
  CRGB &getLED(int, int, int);
  CFastLED &getController();
  int size();

private:
  CRGB _rawleds[LED_STRIP_COUNT][MAX_LED_LENGTH];
  CRGB _ledMatrix[X_LENGTH][Y_LENGTH][Z_LENGTH];
};

#endif