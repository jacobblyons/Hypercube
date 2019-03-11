// pin 8 tan
// pin 9 purple
// pin 10 pink
// pin 11 grey


CRGB &getLED(int x, int y, int z)
{
    //-----------------------------------strips in x direction-----------------------------------
    for (int i = 1; i < 11; i++)
    {
      int lightIndex = i -1;
        //topleft
        if (x == i && y == 11 && z == 11)
            return _rawleds[PURPLE][STRIP_LENGTH - 3 - lightIndex];
        //topright
        if (x == i && y == 11 && z == 0)
            return _rawleds[GREY][STRIP_LENGTH - 1 - 10 + lightIndex];
        //botleft
        if (x == i && y == 0 && z == 11)
            return _rawleds[PINK][10 - 1 - lightIndex];
        //botright
        if (x == i && y == 0 && z == 0){
              return _rawleds[TAN][lightIndex];
        }
    }
    //-----------------------------------strips in y direction-----------------------------------
    for (int i = 1; i < 11; i++)
    {
       int lightIndex = i -1;
        //topleft
        if (x == 0 && y == i && z == 0)
            return _rawleds[GREY][10 - 1 + 1 + lightIndex];
        //topright
        if (x == 11 && y == i && z == 0)
            return _rawleds[TAN][10 - 1+ 1 + lightIndex];

        //botleft
        if (x == 0 && y == i && z == 11)
            return _rawleds[PINK][10 - 1 +1+ lightIndex];
        //botright
        if (x == 11 && y == i && z == 11)
            return _rawleds[PURPLE][10 - 1 + 1 + lightIndex];
    }
    //-----------------------------------strips in z direction-----------------------------------
    for (int i = 0; i < 11; i++)
    {
       int lightIndex = i -1;
        //topleft
        if (x == 0 && y == 11 && z == i)
            return _rawleds[PINK][STRIP_LENGTH - 3 - lightIndex];
        //topright
        if (x == 11 && y == 11 && z == i)
            return _rawleds[TAN][10 -1 + 1 + 10 - 1 + 1 + lightIndex];
        //botleft
        if (x == 0 && y == 0 && z == i)
            return _rawleds[GREY][10 - 1 - lightIndex];
        //botright
        if (x == 11 && y == 0 && z == i)
            return _rawleds[PURPLE][lightIndex];
    }
}

bool hasLED(int x, int y, int z){
  //-----------------------------------strips in x direction-----------------------------------
    for (int i = 1; i < 11; i++)
    {
      int lightIndex = i -1;
        //topleft
        if (x == i && y == 11 && z == 11)
            return true;
        //topright
        if (x == i && y == 11 && z == 0)
            return true;
        //botleft
        if (x == i && y == 0 && z == 11)
            return true;
        //botright
        if (x == i && y == 0 && z == 0){
              return true;
        }
    }
    //-----------------------------------strips in y direction-----------------------------------
    for (int i = 1; i < 11; i++)
    {
       int lightIndex = i -1;
        //topleft
        if (x == 0 && y == i && z == 0)
            return true;
        //topright
        if (x == 11 && y == i && z == 0)
            return true;

        //botleft
        if (x == 0 && y == i && z == 11)
            return true;
        //botright
        if (x == 11 && y == i && z == 11)
            return true;
    }
    //-----------------------------------strips in z direction-----------------------------------
    for (int i = 0; i < 11; i++)
    {
       int lightIndex = i -1;
        //topleft
        if (x == 0 && y == 11 && z == i)
            return true;
        //topright
        if (x == 11 && y == 11 && z == i)
            return true;
        //botleft
        if (x == 0 && y == 0 && z == i)
            return true;
        //botright
        if (x == 11 && y == 0 && z == i)
            return true;
    }
    return false;
}
