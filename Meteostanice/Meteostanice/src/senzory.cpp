#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
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

void sendErrorViaWifi(int id,const char* zaznam){
  //setupWifiCon();
  sendDataViaWifi(id, zaznam);
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
    sendErrorViaWifi(10,"Could not find a valid BMP280 sensor, check wiring!");
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
      Serial.print("Teplota BMP:");
      Serial.println(teplota);
    tlak = bmp.readPressure();
      Serial.print("Tlak BMP:");
      Serial.println(tlak);
    if(!verifyTemperatureBMP280(teplota))
      teplota = 50;
    if(!verifyPressureBMP280(tlak))
      tlak = 0;
    Serial.println("Končím s BMP");
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
      sendErrorViaWifi(15,"ERROR: Data CO2");
      senzoryReset();
      return 0;
    }
  }
  Serial.println("ERROR: Start CO2");
  sendErrorViaWifi(16,"ERROR: Start CO2");
  senzoryReset();
  return 0;
}


/************************************************************
SENZOR BME280
************************************************************/
Adafruit_BME280 bme;
int tlak2;
int vlhkost;
//Adresa I2C pro BMP upravena v knihovně Adafruit_BMP280 na hodnotu 0x76

/*!
* @brief Zapnutí senzoru BMP280
* @return Pokud nastane chyba vrátí true 
*/
bool setupBME280() {
  EEPROM.begin(1);
  Serial.println(F("BME280 test"));
  if (!bme.begin(0x76)) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    sendErrorViaWifi(11,"Could not find a valid BME280 sensor, check wiring!");
    senzoryReset();
    return true;
  }
  return false;
}

bool verifyTemperatureBME280(int teplota){
  if (teplota > 45 || teplota < (-20))
    return false;
  else
    return true;
}
bool verifyPressureBME280(int tlak){
  if (tlak2 > 110000 || tlak2 < 30000)
    return false;
  else
    return true;
}
bool verifyHumidityeBME280(int vlhkost){
  if (vlhkost > 100 || vlhkost < 0)
    return false;
  else
    return true;
}

/*!
 * @brief Čtení hodnot ze senzoru BME280
 * @return Teplota (float)
 */
float readValueBME280() {
  Serial.println("Jsem v BME");
  float teplota;
  teplota = bme.readTemperature();
  teplota = teplota - 0; //Korekce kvůly zahřívání senzoru
    Serial.print("Teplota BME:");
    Serial.print(teplota);
  tlak2 = bme.readPressure();
    Serial.print(",  Tlak BME:");
    Serial.print(tlak2);
  vlhkost = bme.readHumidity();
    Serial.print(",  Vlhkost BME:");
    Serial.println(vlhkost);
  if(!verifyTemperatureBME280(teplota))
    teplota = 50;
  if(!verifyPressureBME280(tlak2))
    tlak2 = 0;
  if (!verifyHumidityeBME280(vlhkost))
    vlhkost = -1;
  
  return teplota;
}