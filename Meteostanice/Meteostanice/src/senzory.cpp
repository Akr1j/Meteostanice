#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include "Adafruit_CCS811.h"
#include <EEPROM.h>

#include <sendViaWifi.h>

/*!
 * @brief Restartování periférií
 */
void senzoryReset(){
  if (EEPROM.read(0) < 4){
    digitalWrite(5,0);
    int pocetRestartu =  EEPROM.read(0);
    Serial.println("EEPROM hodnota: ");
    Serial.println(pocetRestartu);
    EEPROM.write(0,pocetRestartu++);
    delay(500);
    esp_restart();
  }
}

/*!
 * @brief Odesílání chyb přes WiFi
 * Obsahuje i připojení k WiFi
 * @param idChyby
 * @param zaznam popis chyby
 */
void sendErrorViaWifi(int idChyby,const char* zaznam){
  setupWifiCon();
  sendDataViaWifi(idChyby, zaznam);
}

/************************************************************
SENZOR DEŠTĚ
************************************************************/

/*!
 * @brief Zapnutí senzoru deště
 * @param pinSenzoruDeste Číslo pinu na kterém je připojen senzor deště
 */
void setupDestSenzor(const int pinSenzoruDeste){
  pinMode(pinSenzoruDeste,INPUT);
}

/*!
 * @brief Čtení hodnot z senzoru deště
 * @return true pokud je senzor mokrý
 */
bool isPrsi(const int pinSenzoruDeste){
  return !(digitalRead(pinSenzoruDeste));
}

/************************************************************
SENZOR CO2
************************************************************/
Adafruit_CCS811 ccs;

/*!
 * @brief Zapnití senzoru CCS811
 * @return 0 po zapnutí senzoru
 */
bool setupCCS811() { 
  ccs.begin();
  while(!ccs.available());
  return 0;
}

/*!
 * @brief Kontrola hodnoty zda se nachází ve vymezeném rozmezí
 * @return 0 pokud není v rozmezí
 */
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
  else{
    Serial.println("ERROR: Start CO2");
    sendErrorViaWifi(16,"ERROR: Start CO2");
    senzoryReset();
    return 0;
  }
}


/************************************************************
SENZOR BME280
************************************************************/
Adafruit_BME280 bme;

//Adresa I2C pro BME upravena v knihovně Adafruit_BMP280 na hodnotu 0x76

/*!
* @brief Zapnutí senzoru BME280
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

/*!
 * @brief Kontrola hodnoty zda se nachází ve vymezeném rozmezí
 * @return 0 pokud není v rozmezí
 */
bool verifyTemperatureBME280(int teplota){
  if (teplota > 45 || teplota < (-20))
    return false;
  else
    return true;
}

/*!
 * @brief Kontrola hodnoty zda se nachází ve vymezeném rozmezí
 * @return 0 pokud není v rozmezí
 */
bool verifyPressureBME280(int tlak){
  if (tlak > 110000 || tlak < 30000)
    return false;
  else
    return true;
}

/*!
 * @brief Kontrola hodnot zda se nachází ve vymezeném rozmezí
 * @return 0 pokud není v rozmezí
 */
bool verifyHumidityBME280(int vlhkost){
  if (vlhkost > 100 || vlhkost < 0)
    return false;
  else
    return true;
}

/*!
 * @brief Čtení hodnot ze senzoru BME280
 * @return Pole hodnot {Teplota, Tlak, Vlhkost} (double *)
 */
double * readValueBME280() {
  Serial.println("Začátek snímání BME");
  static double values[3]; // {Teplota, Tlak, Vlhkost}

  values[0] = bme.readTemperature();
    Serial.print("Teplota BME:");
    Serial.print(values[0]);

  values[1] = bme.readPressure();
    Serial.print(",  Tlak BME:");
    Serial.print(values[1]);

  values[2] = bme.readHumidity();
    Serial.print(",  Vlhkost BME:");
    Serial.println(values[2]);

  if(!verifyTemperatureBME280(values[0]))
    values[0] = 50;
  if(!verifyPressureBME280(values[1]))
    values[1] = 0;
  if (!verifyHumidityBME280(values[2]))
    values[2] = -1;
  
  return values;
}