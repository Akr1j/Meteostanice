#include <Arduino.h>

void zapniSerial(int rychlost){
    Serial.begin(rychlost);
    while (!Serial);
    Serial.println("");
}

void porty(){
  pinMode(5, OUTPUT);
  digitalWrite(5,1);
}