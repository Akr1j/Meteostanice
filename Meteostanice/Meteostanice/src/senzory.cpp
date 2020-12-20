#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>

//Adresa I2C pro BMP upravena v knihovně Adafruit_BMP280 na hodnotu 0x76

#define rainDigital 34 //Port pro připojení senzoru deště
int tlak;

void setupDestSenzor(){
      pinMode(rainDigital,INPUT);
}

//Pokud je senzor mokrý - 1 jinak 0
bool isPrsi(){
  return !(digitalRead(rainDigital));
}





Adafruit_BMP280 bmp; // I2C

void setupBMP280() {
  Serial.println(F("BMP280 test"));
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
}

int readValueBMP280() {
  int teplota;

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