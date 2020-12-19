  #include <Arduino.h>

  void zapniSerial(int rychlost){
      Serial.begin(rychlost);
      while (!Serial);
      Serial.println("");
  }
