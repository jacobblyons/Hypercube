int r = 6;
int rfCount = 0;
void risingFallingPattern(){
  rfCount =  (rfCount + 1) % 25;

  for(int x = 0; x < 12 ; x++) {
    for(int y = 0; y < 12 ; y++) {
      for(int z = 0; z < 12 ; z++) {
         if(!hasLED(x,y,z)) continue;
         if(y >  rfCount ) continue;
         getLED(x,y,z) = CHSV(rfCount* (255/12),255,255);
      }

    }
  }
  int sonarValue = (analogRead(0)*5)/25.4;
  FastLED.show();
  Serial.println(10*sonarValue);
  delay(10 *sonarValue);

}

void sonarDistance(int sonar) {

  for(int x = 0; x < 12 ; x++) {
    for(int y = 0; y < 12 ; y++) {
      for(int z = 0; z < 12 ; z++) {
        if(!hasLED(x,y,z)) continue;
        if( sonar < 10) getLED(x,y,z) = CRGB::Red;
        else getLED(x,y,z) = CRGB::Blue;
      }

    }
  }

  FastLED.show();
  FastLED.delay(10 * sonar);

}

void distancePattern(int dist){



  for(int x = 0; x < 12 ; x++) {
    for(int y = 0; y < 12 ; y++) {
      for(int z = 0; z < 12 ; z++) {
         if(!hasLED(x,y,z)) continue;
         if(z >  dist ) continue;
         getLED(x,y,z) = CHSV(rfCount* (255/12),255,255);
      }

    }
  }

  FastLED.show();
  FastLED.delay(100);

}

void pulsingPattern(int delayTime){
  rfCount =  (rfCount + 1) % 25;

  for(int x = 0; x < 12 ; x++) {
    for(int y = 0; y < 12 ; y++) {
      for(int z = 0; z < 12 ; z++) {
         if(!hasLED(x,y,z)) continue;
         getLED(x,y,z) = CHSV(rfCount* (255/12),255,255);
      }

    }
  }

  FastLED.show();
  FastLED.delay(delayTime);

}

void spherePattern() {
  r = (r +1) % 40;
  for(int x = 0; x < 12 ; x++) {
    for(int y = 0; y < 12 ; y++) {
      for(int z = 0; z < 12 ; z++) {
        //if in sphere, display LED
        if(inSphere(x,y,z,0,0,0,r)){
          if(!hasLED(x,y,z)) continue;
          getLED(x,y,z) = CRGB::Red;
          FastLED.show();
        }
        else {
          if(!hasLED(x,y,z)) continue;
          getLED(x,y,z) = CRGB::Blue;
          FastLED.show();
        }
      }
    }
  }

  //?FastLED.delay(20);

}

void exampleDemo(int delayTime){
    // rfCount =  (rfCount + 1) % 25;
    for(int x = 0; x < 12 ; x++) {
      for(int y = 0; y < 12 ; y++) {
        for(int z = 0; z < 12 ; z++) {
           if(!hasLED(x,y,z)) continue;
           getLED(x,y,z) = CHSV(160,255,255);   // Blue
           FastLED.show();
           FastLED.delay(10);
           getLED(x,y,z) = CHSV(0,0,0);
           FastLED.show();
           FastLED.delay(5);
        }
      }
    }

}

bool inSphere(int x, int y, int z, int cx, int cy, int cz, int r){
  return (pow(x - cx, 2) + pow(y - cy, 2) + pow(z - cz, 2)) < r && (pow(x - cx, 2) + pow(y - cy, 2) + pow(z - cz, 2)) > r-2;
}
