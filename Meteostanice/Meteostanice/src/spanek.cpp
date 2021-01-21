#include <Arduino.h>
#include <sys/types.h>
#include <sys/time.h>

#include <sendViaWifi.h>

/*!
 * @brief Uspání zařízení
 * @param sleepTime Doba spánku (ve vteřinách)
 */
void usni(const int sleepTime){
  esp_deep_sleep(sleepTime * 1000000); //Uspání zařízení na dobu v proměné sleepTime
}

/*!
 * @brief Akce po ukradnutí zařízení
 */
void kradez(const char* ssid, const char* password, const int sleepTime, const char* server_pohyb){
  Serial.println("Ukradnuto");
  setupWifiCon(ssid, password);
  sendDataViaWifi(server_pohyb);
  usni(sleepTime);
}

RTC_DATA_ATTR long int casSpankuStary; //Čas ukládaný i přes deepSleep
/*!
 * @brief Kontrola zda bylo zařízení ukradnuto
 * @param ssid Název WIFI
 * @param password Heslo k WIFI
 * @param sleepTime Doba spánku (ve vteřinách)
 */
void timeChecker(const char* ssid, const char* password, const int sleepTime, const int rozptylCasu, const char* server_pohyb) {
  struct timeval tv_now;
  static uint64_t sleep_start_us = 0;
  sleep_start_us = gettimeofday(&tv_now,NULL);
  time_t now;
  time(&now);
  long int casSpanku = now;

  if (casSpanku - casSpankuStary < sleepTime - rozptylCasu)
  {
    kradez(ssid, password, sleepTime, server_pohyb);
  }
  casSpankuStary = casSpanku;
}