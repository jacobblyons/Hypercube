const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
 
void setup() 
{
   Serial.begin(9600);
}
 
 
//void loop() 
{  //Audio Signal Processing
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
 
   Serial.println(audio_volts);
//} 
//reset all leds back to black from last audio pass
  for (int i = 0 ; i < STRIP_LENGTH; i ++) {
    _rawleds[0][i] = CRGB::Black;
    _rawleds[1][i] = CRGB::Black
    _rawleds[2][i] = CRGB::Black
    _rawleds[3][i] = CRGB::Black
    FastLED.show();
 }

//assuming max voltage ~= 4V, will need to scale adjustment based on mic tuning/gain,
    int scale = 10; //bottom strip always lit
    if (audio_volts <1){
      scale = 12;
    }
    if (audio_volts < 2 && audio_volts > 1){
      scale = 15; 
    }
    if (audio_volts < 3 && audio_volts > 2){
     scale = 17;
    }
    if (audio_volts < 4 && audio_volts > 3){
     scale = 19;
    }
    if(audio_volts > 4){
      scale = STRIP_LENGTH
    }
    
    for (int i = 0 ; i < scale; i ++) {
      if (scale < 10){
        _rawleds[0][i] = CRGB::Green;
        _rawleds[1][i] = CRGB::Green;
        _rawleds[2][i] = CRGB::Green;
        _rawleds[3][i] = CRGB::Green;
      }
      if (scale > 10 && scale <20){
        _rawleds[0][i] = CRGB::Yellow;
        _rawleds[1][i] = CRGB::Yellow;
        _rawleds[2][i] = CRGB::Yellow;
        _rawleds[3][i] = CRGB::Yellow;
      }
      if(scale > 20){
        _rawleds[0][i] = CRGB::Red;
        _rawleds[1][i] = CRGB::Red;
        _rawleds[2][i] = CRGB::Red;
        _rawleds[3][i] = CRGB::Red;
      }
  }
  FastLED.show(); //display current levels
  
