//#include <Arduino.h>

#include <spanek.h>
#include <senzory.h>
#include <startup.h>
#include <sendViaWifi.h>

const char* ssid = "Jandourek";
const char* password = "hesloProNarusitele";

const char* server_data = "http://207.180.232.51:8888/novaData";

void setup() {
  zapniSerial(9600);
  porty();
  setupBMP280();
  setupCCS811();
  setupDestSenzor();
  setupWifiCon(ssid, password);
}

void loop() {
  timeChecker();

  bool zda_prsi = isPrsi();
  
  float data_BMP = readValueBMP280();

  int co2 = readValueCCS811();

  sendDataViaWifi(server_data, data_BMP, 0, tlak, co2, zda_prsi);
  usni();
}