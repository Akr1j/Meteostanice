//#include <Arduino.h>

#include <spanek.h>
#include <senzory.h>
#include <startup.h>
#include <sendViaWifi.h>

const char* ssid = "Jandourek";
const char* password = "hesloProNarusitele";

const char* server_data = "http://207.180.232.51:8888/novaData";

bool err_bmp280;
float data_BMP;

void setup() {
  zapniSerial(9600);
  timeChecker(ssid, password);
  porty();
  err_bmp280 = setupBMP280();
  setupCCS811();
  setupDestSenzor();
  setupWifiCon(ssid, password);
  data_BMP = 50;
  tlak = 0;
}

void loop() {

  bool zda_prsi = isPrsi();
  
  if (!err_bmp280)
    data_BMP = readValueBMP280();
  

  int co2 = readValueCCS811();

  sendDataViaWifi(server_data, data_BMP, 0, tlak, co2, zda_prsi);
  usni();
}