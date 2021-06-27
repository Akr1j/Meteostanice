#include <spanek.h>
#include <senzory.h>
#include <startup.h>
#include <sendViaWifi.h>
#include <Arduino.h>

const int sleepTime = 30; //Doba spánku (ve vteřinách)
#define rozptylCasu 1 //Rozsah korekce času (časovač se posunuje. Zde doba kdy se vyhlásí poplach)

const int pinSenzoruDeste = 34; //Port pro připojení senzoru deště

bool err_bme280;
bool err_CCS811;
double *data_BME;
int data_CCS811;

void setup() {

  zapniSerial(9600);
  timeChecker(sleepTime, rozptylCasu);
  setupPorty();

  err_bme280 = setupBME280();
  if (!err_bme280)
    Serial.println("Test BME úspěšný");
  else
    Serial.println("Test BME neúspěšný");
  
  err_CCS811 = setupCCS811();
  if (!err_CCS811)
    Serial.println("Test CCS811 úspěšný");
  else
    Serial.println("Test CCS811 neúspěšný");

  setupDestSenzor(pinSenzoruDeste);
  
  Serial.println("Před nastavením WIFI");
  if (!setupWifiCon())
    Serial.println("Připojení k WiFi úspěšné");
  else
    Serial.println("Připojení k WiFi neúspěšné");

  Serial.println("Nastavení hotové");
}

void loop() {

  if (!err_bme280)
  {
    data_BME = readValueBME280();
      Serial.print("Výpis:");
      Serial.print(*data_BME);
      Serial.print( " Tlak ");
      Serial.print(*(data_BME + 1));
      Serial.print( " Vlhkost ");
      Serial.println(*(data_BME + 2));
    Serial.println("Jsem za BME");
  }
  
  if (!err_CCS811)
  {
    data_CCS811 = readValueCCS811();
  }
  sendDataViaWifi(*data_BME, *(data_BME + 2), *(data_BME + 1), data_CCS811, isPrsi(pinSenzoruDeste));

  usni(sleepTime);
}