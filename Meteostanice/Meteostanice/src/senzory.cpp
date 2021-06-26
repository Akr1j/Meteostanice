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
SENZOR CO2
************************************************************/

void setupI2C()
{
  Wire.begin();
 
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}
void loopI2C()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
}





Adafruit_CCS811 ccs;

/*!
 * @brief Zapnití senzoru CCS811
 */
bool setupCCS811() { 
  ccs.begin();
  while(!ccs.available());
  return 0;
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
  setupI2C();
  loopI2C();
  if(ccs.available()){
    //delay(5000); //Čas pro stabilizování senzoru !! Mělo by být 20min není možni viz.dokumentace
    if(!ccs.readData()){
      int co2 = ccs.geteCO2();
      if (!verifyValueCCS811(co2))
        co2 = 0;
      return co2;
    }
    else{
      Serial.println("ERROR: Data CO2");
      //sendErrorViaWifi(15,"ERROR: Data CO2");
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

bool verifyTemperatureBME280(int teplota){
  if (teplota > 45 || teplota < (-20))
    return false;
  else
    return true;
}
bool verifyPressureBME280(int tlak){
  if (tlak > 110000 || tlak < 30000)
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
double * readValueBME280() {
  Serial.println("Začátek snímání BME");
  static double values[3]; // {Teplota, Tlak, Vlhkost}

  values[0] = bme.readTemperature();
    Serial.print("Teplota BME:");
    Serial.print(values[0]);

  values[1] = bme.readPressure();
    Serial.print(",  Tlak BME:");
    Serial.print(values[1]);
    //Serial.print(tlak2);

  values[2] = bme.readHumidity();
    Serial.print(",  Vlhkost BME:");
    Serial.println(values[2]);
    //Serial.println(vlhkost);

/*
  if(!verifyTemperatureBME280(values[0]))
    values[0] = 50;
  if(!verifyPressureBME280(values[1]))
    values[1] = 0;
  if (!verifyHumidityeBME280(values[2]))
    values[2] = -1;*/
  
  return values;
}