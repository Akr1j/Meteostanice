#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "Adafruit_CCS811.h"

#include <conf.h>

//Adresa I2C pro BMP upravena v knihovně Adafruit_BMP280 na hodnotu 0x76

extern const int pin_pro_dest;
int tlak;

void setupDestSenzor(){
  pinMode(pin_pro_dest,INPUT);
}

//Pokud je senzor mokrý => 1 jinak 0
bool isPrsi(){
  return !(digitalRead(pin_pro_dest));
}

void senzoryReset(){
  digitalWrite(5,0);
  delay(500);
  esp_restart();
}


/*
SENZOR TEPLOTY, TLAKU
*/
Adafruit_BMP280 bmp;

void setupBMP280() {
  Serial.println(F("BMP280 test"));
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    senzoryReset();
  }
}

float readValueBMP280() {
  float teplota;
  //int vlhkost;
    teplota = bmp.readTemperature();
    tlak = bmp.readPressure();
    return teplota;
}

/*
SENZOR CO2
*/
Adafruit_CCS811 ccs;

void setupCCS811() { 
  ccs.begin();
  while(!ccs.available());
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 25.0);
}

int readValueCCS811() {
  if(ccs.available()){
    delay(5000);
    if(!ccs.readData()){
      int co2 = ccs.geteCO2();
      return co2;
    }
    else{
      Serial.println("ERROR: CO2");
      senzoryReset();
      return 0;
    }
  }
  senzoryReset();
  return 0;
}