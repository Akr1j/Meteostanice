#include <Arduino.h>

#include <spanek.h>
#include <senzory.h>
#include <startup.h>

void setup() {
  zapniSerial(9600);
  setupBMP280();
  setupDestSenzor();
}

void loop() {
  timeChecker();

  Serial.print("Zda prší: ");
  Serial.println(isPrsi());
  
  readValueBMP280();

  usni();
}