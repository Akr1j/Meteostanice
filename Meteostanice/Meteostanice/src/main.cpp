#include <Arduino.h>
#include <sys/types.h>
#include <sys/time.h>

/* LZE OTESTOVAT AŽ PO NAPÁJENÍ BMP280
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
*/

#define dobaSpanku 5 //Doba spánku (ve vteřinách)
#define rozptylCasu 1 //Rozsah korekce času (časovač se posunuje zde doba kdy se vyhlásí poplach)


#define rainDigital 34 //Port pro připojení senzoru deště

int sleepTime = dobaSpanku; //Doba spánku (ve vteřinách)
boolean dest; //Pokud je senzor mokrý - 1 jinak 0

//Hodnoty pro práci s časem (Probuzení a kontrola času spánku)
static uint64_t sleep_start_us = 0;
struct timeval tv_now;
RTC_DATA_ATTR long int casSpankuStary; //hodnota ukládaná i přes deepSleep




/* LZE OTESTOVAT AŽ PO NAPÁJENÍ BMP280
Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();
*/






void kradez(){
  Serial.println("Ukradnuto");
}

void timeChecker() {  //Funkce pro kontrolu zda bylo zařízení ukradnuto
  sleep_start_us = gettimeofday(&tv_now,NULL);
  time_t now;
  time(&now);
  long int casSpanku = now;

  if (casSpanku - casSpankuStary < sleepTime - rozptylCasu)
  {
    kradez();
  }

  Serial.println();
  Serial.println("casSpanku:" + casSpanku);
  Serial.println("casSpankuStary" + casSpankuStary);
  casSpankuStary = casSpanku;
}








/*  LZE OTESTOVAT AŽ PO NAPÁJENÍ BMP280

void BMP280Start() {
  Serial.println(F("BMP280 Sensor event test"));

  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1) delay(10);
  }

  // Default settings from datasheet.
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     // Operating Mode.
                  Adafruit_BMP280::SAMPLING_X2,     // Temp. oversampling 
                  Adafruit_BMP280::SAMPLING_X16,    // Pressure oversampling 
                  Adafruit_BMP280::FILTER_X16,      // Filtering. 
                  Adafruit_BMP280::STANDBY_MS_500); // Standby time. 

  bmp_temp->printSensorDetails();
}

void BMP280Read() {
  sensors_event_t temp_event, pressure_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  
  Serial.print(F("Temperature = "));
  Serial.print(temp_event.temperature);
  Serial.println(" *C");

  Serial.print(F("Pressure = "));
  Serial.print(pressure_event.pressure);
  Serial.println(" hPa");

  Serial.println();
  delay(2000);
}

*/











void setup() {
  Serial.begin(9600);

  //BMP280Start();  LZE OTESTOVAT AŽ PO NAPÁJENÍ BMP280

  pinMode(rainDigital,INPUT);
}

void loop() {
  timeChecker();


  dest = !(digitalRead(rainDigital)); // kontrola zda prší
  Serial.println(dest);

  //BMP280Read();   LZE OTESTOVAT AŽ PO NAPÁJENÍ BMP280
  
  esp_deep_sleep(sleepTime * 1000000); //Uspání zařízení na dobu v proměné sleepTime
}