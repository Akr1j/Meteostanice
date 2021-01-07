#include <Arduino.h>
#include <sys/types.h>
#include <sys/time.h>

#include <sendViaWifi.h>

#define dobaSpanku 30 //Doba spánku (ve vteřinách)
#define rozptylCasu 1 //Rozsah korekce času (časovač se posunuje. Zde doba kdy se vyhlásí poplach)

const char* server_pohyb = "http://207.180.232.51:8888/kradez";

const int sleepTime = dobaSpanku; //Doba spánku (ve vteřinách)

/*
 *Hodnoty pro práci s časem (Probuzení a kontrola času spánku)
 */

static uint64_t sleep_start_us = 0;
struct timeval tv_now;
RTC_DATA_ATTR long int casSpankuStary; //hodnota ukládaná i přes deepSleep

/*
Uspání zařízení
*/
void usni(){
  esp_deep_sleep(sleepTime * 1000000); //Uspání zařízení na dobu v proměné sleepTime
}

/*
Metoda která se vyvolá po ukradnutí
*/
void kradez(){
  Serial.println("Ukradnuto");
  sendDataViaWifi(server_pohyb);
  usni();
}

/*
Funkce pro kontrolu zda bylo zařízení ukradnuto
*/
void timeChecker() {
  sleep_start_us = gettimeofday(&tv_now,NULL);
  time_t now;
  time(&now);
  long int casSpanku = now;

  if (casSpanku - casSpankuStary < sleepTime - rozptylCasu)
  {
    kradez();
  }
  casSpankuStary = casSpanku;
}