#include <spanek.h>
#include <senzory.h>
#include <startup.h>
#include <sendViaWifi.h>
#include <Arduino.h>

const int sleepTime = 30; //Doba spánku (ve vteřinách)
#define rozptylCasu 1 //Rozsah korekce času (časovač se posunuje. Zde doba kdy se vyhlásí poplach)

const int pin_pro_dest = 34; //Port pro připojení senzoru deště

bool err_bmp280;
bool err_bme280;
float data_BMP;
double *data_BME;

void setup() {
  zapniSerial(9600);
  //timeChecker(sleepTime, rozptylCasu);
  setupPorty();
  //err_bmp280 = setupBMP280();
  err_bme280 = setupBME280();
  if (!err_bme280)
    Serial.println("Test BME úspěšný");
  
  setupCCS811();
  Serial.println("Po zapnutí CO2");
  setupDestSenzor(pin_pro_dest);
  Serial.println("Před nastavením WIFI");
  setupWifiCon();
  data_BMP = 50; //Defaultní hodnota (V případě chyby)
  tlak = 0; //Defaultní hodnota (V případě chyby)
  Serial.println("Nastavení hotové");
}

void loop() {
  bool zda_prsi = isPrsi(pin_pro_dest);

  if (!err_bme280)
    data_BME = readValueBME280();
    Serial.print("Výpis:");
    Serial.print(*data_BME);
    Serial.print( " Tlak ");
    Serial.print(*(data_BME + 1));
    Serial.print( " Vlhkost ");
    Serial.println(*(data_BME + 2));
  Serial.println("Jsem za BME");
  
 tlak = tlak + tlak2;
  int co2 = readValueCCS811();

  sendDataViaWifi(*data_BME, *(data_BME + 1), *(data_BME + 2), co2, zda_prsi);
  usni(sleepTime);
}