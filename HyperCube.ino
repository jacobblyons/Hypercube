#include <LEDCube.h>

LEDCube c;

void setup()
{
    c = LEDCube();
    c.getController();
    c.getLED(0,0,0).setRGB(255,255,20);
}

void loop()
{
}
