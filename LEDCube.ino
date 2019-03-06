CRGB &getLED(int x, int y, int z)
{

    //-----------------------------------strips in x direction-----------------------------------
    //top
    for (int i = 0; i < LEDS_ON_TOP; i++)
    {
        //left
        if (x == i && y == LEDS_ON_SIDES - 1 && z == LEDS_ON_TOP - 1)
            return _rawleds[PURPLE][LEDS_ON_TOP - 1 - i];
        //right
        if (x == i && y == LEDS_ON_SIDES - 1 && z == 0)
            return _rawleds[GREY][STRIP_LENGTH - LEDS_ON_TOP - 1 + i];
    }

    //bot
    for (int i = 0; i < LEDS_ON_BOT; i++)
    {
        //left
        if (x == i && y == 0 && z == LEDS_ON_BOT - 1)
            return _rawleds[PINK][LEDS_ON_BOT - 1 - i];
        //right
        if (x == i && y == 0 && z == 0){
              return _rawleds[TAN][i];
        }
          
           
    }

    //-----------------------------------strips in y direction-----------------------------------
    //top
    for (int i = 0; i < LEDS_ON_SIDES; i++)
    {
        //left
        if (x == 0 && y == i && z == 0)
            return _rawleds[GREY][LEDS_ON_BOT - 1 + i];
        //right
        if (x == LEDS_ON_BOT - 1 && y == i && z == 0)
            return _rawleds[TAN][LEDS_ON_BOT - 1 + i];
    }

    //bot
    for (int i = 0; i < LEDS_ON_SIDES; i++)
    {
        //left
        if (x == 0 && y == i && z == LEDS_ON_BOT - 1)
            return _rawleds[PINK][LEDS_ON_BOT - 1 + i];
        //right
        if (x == LEDS_ON_BOT - 1 && y == i && z == LEDS_ON_BOT - 1)
            return _rawleds[PURPLE][LEDS_ON_BOT - 1 + i];
    }
    //-----------------------------------strips in z direction-----------------------------------
    //top
    for (int i = 0; i < LEDS_ON_TOP; i++)
    {
        //left
        if (x == 0 && y == LEDS_ON_SIDES - 1 && z == i)
            return _rawleds[PINK][STRIP_LENGTH - 1 - i];
        //right
        if (x == LEDS_ON_TOP - 1 && y == LEDS_ON_SIDES - 1 && z == i)
            return _rawleds[TAN][LEDS_ON_BOT + LEDS_ON_SIDES - 1 + i];
    }

    //bot
    for (int i = 0; i < LEDS_ON_TOP; i++)
    {
        //left
        if (x == 0 && y == 0 && z == i)
            return _rawleds[GREY][LEDS_ON_BOT - 1 - i];
        //right
        if (x == LEDS_ON_BOT - 1 && y == 0 && z == i)
            return _rawleds[PURPLE][i];
    }
}
