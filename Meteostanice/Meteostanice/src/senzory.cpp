#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <SPI.h>

//Adresa I2C pro BMP upravena v knihovně Adafruit_BMP280 na hodnotu 0x76

#define rainDigital 34 //Port pro připojení senzoru deště
boolean zda_prsi; //Pokud je senzor mokrý - 1 jinak 0

void setupDestSenzor(){
      pinMode(rainDigital,INPUT);
}

bool isPrsi(){
    zda_prsi = !(digitalRead(rainDigital)); // kontrola zda prší
    if (zda_prsi)
      return 1;
    else
      return 0;
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
  int hodnoty[2];
    Serial.print(("Temperature = "));
    hodnoty[0] = bmp.readTemperature();
    Serial.print(hodnoty[0]);
    Serial.println(" *C");

    Serial.print(("Pressure = "));
    hodnoty[1] = bmp.readPressure();
    Serial.print(hodnoty[1]);
    Serial.println(" Pa");

    Serial.print("Approx altitude = ");
    Serial.print(bmp.readAltitude(1013.25));
    Serial.println(" m");

    Serial.println();
    delay(2000);

    return hodnoty[0];
}