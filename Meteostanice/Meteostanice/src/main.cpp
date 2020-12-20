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
}

void loop() {
  timeChecker();


  bool zda_prsi = isPrsi();
  Serial.print("Zda prší: ");
  Serial.println(zda_prsi);
  
  int data_BMP = readValueBMP280();

  sendDataViaWifi(data_BMP,0,tlak,40);
  usni();
}