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

int verifyTemperatureBMP280(int teplota){
  if (teplota > 45 || teplota < (-20))
    return false;
  else
    return true;
}
int verifyPressureBMP280(int tlak){
  if (tlak > 110000 || tlak < 30000)
    return false;
  else
    return true;
}

float readValueBMP280() {
  float teplota;
  //int vlhkost;
    teplota = bmp.readTemperature();
    teplota = -200;
    tlak = bmp.readPressure();
    tlak = 0;
    if(!verifyTemperatureBMP280(teplota))
      teplota = 50;
    if(!verifyPressureBMP280(tlak))
      tlak = 0;
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

bool verifyValueCCS811(int hodnota){
  if (hodnota > 8192 || hodnota < 400)
    return false;
  else
    return true;
}

int readValueCCS811() {
  if(ccs.available()){
    delay(5000);
    if(!ccs.readData()){
      int co2 = ccs.geteCO2();
      co2 = 0;
      if (!verifyValueCCS811(co2))
        co2 = 0;
      
      return co2;
    }
    else{
      Serial.println("ERROR: Data CO2");
      senzoryReset();
      return 0;
    }
  }
  Serial.println("ERROR: Start CO2");
  senzoryReset();
  return 0;
}