#include <Arduino.h>

#include <spanek.h>
#include <senzory.h>
#include <startup.h>
#include <sendViaWifi.h>


void setup() {
  zapniSerial(9600);
  setupBMP280();
  setupDestSenzor();
  setupWifiCon();

  setupCCS811();
}

void loop() {
  timeChecker();


  bool zda_prsi = isPrsi();
  Serial.print("Zda prší: ");
  Serial.println(zda_prsi);
  
  float data_BMP = readValueBMP280();

  int co2 = readValueCCS811();

  sendDataViaWifi(data_BMP,0,tlak,co2, zda_prsi);
  usni();
}