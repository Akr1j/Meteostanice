#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>

#include <conf.h>

//Adresa I2C pro BMP upravena v knihovně Adafruit_BMP280 na hodnotu 0x76

extern const int pin_pro_dest;
int tlak;

void setupDestSenzor(){
      pinMode(pin_pro_dest,INPUT);
}

//Pokud je senzor mokrý - 1 jinak 0
bool isPrsi(){
  return !(digitalRead(pin_pro_dest));
}





Adafruit_BMP280 bmp; // I2C

void setupBMP280() {
  Serial.println(F("BMP280 test"));
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    digitalWrite(5,0);
    delay(1000);
    esp_restart();
  }
}

float readValueBMP280() {
  float teplota;

  int vlhkost;
    Serial.print(("Temperature = "));
    teplota = bmp.readTemperature();
    Serial.print(teplota);
    Serial.println(" *C");

    Serial.print(("Pressure = "));
    tlak = bmp.readPressure();
    Serial.print(tlak);
    Serial.println(" Pa");

    Serial.print("Approx altitude = ");
    Serial.print(bmp.readAltitude(1013.25));
    Serial.println(" m");

    Serial.println();
    delay(2000);

    return teplota;
}





#include "Adafruit_CCS811.h"

Adafruit_CCS811 ccs;

void setupCCS811() { 
  ccs.begin();
  //calibrate temperature sensor
  while(!ccs.available());
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 25.0);
}


int readValueCCS811() {
  if(ccs.available()){
    float temp = ccs.calculateTemperature();
    delay(5000);
    if(!ccs.readData()){
      int co2 = ccs.geteCO2();
      int tvoc = ccs.getTVOC();
      Serial.println(String ("CO2:")+ String (co2)+String(" PPM"));
      Serial.println(String ("TVOC:")+ String (tvoc)+String(" PPB "));
      Serial.println(String("T:"+String (int(temp)))+String("C"));
      return co2;
    }
    else{
      Serial.println("ERROR: CO2");
      return 0;
    }
  }
  return 0;
}