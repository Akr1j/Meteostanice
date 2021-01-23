#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include "Adafruit_CCS811.h"
#include <EEPROM.h>

#include <sendViaWifi.h>

/*!
 * @brief Restartování periférií
 */
void senzoryReset(){
  if (EEPROM.read(0) < 4){
    digitalWrite(5,0);
    int number_of_restarts =  EEPROM.read(0);
    Serial.println("EEPROM hodnota: ");
    Serial.println(number_of_restarts);
    EEPROM.write(0,number_of_restarts++);
    delay(500);
    esp_restart();
  }
}

/************************************************************
SENZOR DEŠTĚ
************************************************************/

/*!
 * @brief Zapnutí senzoru deště
 */
void setupDestSenzor(const int pin_pro_dest){
  pinMode(pin_pro_dest,INPUT);
}

/*!
 * @brief Čtení hodnot z senzoru deště
 * @return Senzor mokrý => true
 */
bool isPrsi(const int pin_pro_dest){
  return !(digitalRead(pin_pro_dest));
}

/************************************************************
SENZOR BMP280
************************************************************/
Adafruit_BMP280 bmp;
int tlak;
//Adresa I2C pro BMP upravena v knihovně Adafruit_BMP280 na hodnotu 0x76

/*!
* @brief Zapnutí senzoru BMP280
* @return Pokud nastane chyba vrátí true 
*/
bool setupBMP280() {
  EEPROM.begin(1);
  Serial.println(F("BMP280 test"));
  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    senzoryReset();
    return true;
  }
  return false;
}

bool verifyTemperatureBMP280(int teplota){
  if (teplota > 45 || teplota < (-20))
    return false;
  else
    return true;
}
bool verifyPressureBMP280(int tlak){
  if (tlak > 110000 || tlak < 30000)
    return false;
  else
    return true;
}

/*!
 * @brief Čtení hodnot ze senzoru BMP280
 * @return Teplota (float)
 */
float readValueBMP280() {
  float teplota;
  //int vlhkost;
    teplota = bmp.readTemperature();
    teplota = teplota - 1.5; //Korekce kvůly zahřívání senzoru
    tlak = bmp.readPressure();
    if(!verifyTemperatureBMP280(teplota))
      teplota = 50;
    if(!verifyPressureBMP280(tlak))
      tlak = 0;
    return teplota;
}

/************************************************************
SENZOR CO2
************************************************************/
Adafruit_CCS811 ccs;

/*!
 * @brief Zapnití senzoru CCS811
 */
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

/*!
 * @brief Čtení hodnot ze senzoru CCS811
 * @return Hodnota CO2 (int)
 */
int readValueCCS811() {
  if(ccs.available()){
    delay(5000); //Čas pro stabilizování senzoru !! Mělo by být 20min není možni viz.dokumentace
    if(!ccs.readData()){
      int co2 = ccs.geteCO2();
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