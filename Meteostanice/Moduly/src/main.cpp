#include <Arduino.h>

#define rainDigital 34

void setup() {
  Serial.begin(9600);
  pinMode(rainDigital,INPUT);
}
void loop() {
  boolean bIsRaining = !(digitalRead(rainDigital)); // Pokud prší tak je v bIsRaining uložena 1 jinak 0
  Serial.println(bIsRaining);
  delay(200);
}