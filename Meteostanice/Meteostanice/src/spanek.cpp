#include <Arduino.h>
#include <sys/types.h>
#include <sys/time.h>

#include <sendingDataViaWiFi/sendViaWifi.h>

/*!
 * @brief Uspání zařízení
 * @param sleepTime Doba spánku (ve vteřinách)
 */
void usni(const int sleepTime){
  esp_deep_sleep(sleepTime * 1000000); //Uspání zařízení na dobu v proměné sleepTime
}

/*!
 * @brief Akce po ukradnutí zařízení
 * @param sleepTime Čas po jakou dobu se má meteostanice uspat
 */
void kradez(const int sleepTime){
  Serial.println("Ukradnuto");
  setupWifiCon();
  sendDataViaWifi();
  usni(sleepTime);
}

RTC_DATA_ATTR long int casSpankuStary; //Čas ukládaný i přes deepSleep
/*!
 * @brief Kontrola zda bylo zařízení ukradnuto
 * @param sleepTime Doba spánku (ve vteřinách)
 * @param rozptylCasu Doba které se toleruje z důvodů chybovosti časovače
 */
void timeChecker(const int sleepTime, const int rozptylCasu) {
  time_t now;
  time(&now);
  long int casSpanku = now;

  if (casSpanku - casSpankuStary < sleepTime - rozptylCasu)
  {
    kradez(sleepTime);
  }
  casSpankuStary = casSpanku;
}