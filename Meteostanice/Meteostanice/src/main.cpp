#include <Arduino.h>

#include <spanek.h>
#include <senzory.h>
#include <startup.h>
#include <sendViaWifi.h>

int data_BMP;
void setup() {
  zapniSerial(9600);
  setupBMP280();
  setupDestSenzor();
  setupWifiCon();
}

void loop() {
  timeChecker();

  Serial.print("Zda prší: ");
  Serial.println(isPrsi());
  
  data_BMP = readValueBMP280();

  sendDataViaWifi(data_BMP,20,1000,40);
  usni();
}