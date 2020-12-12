#include <Arduino.h>
#include <sys/types.h>
#include <sys/time.h>

#define dobaSpanku 5 //Doba spánku (ve vteřinách)
#define rozptylCasu 1 //Rozsah korekce času (časovač se posunuje zde doba kdy se vyhlásí poplach)

int sleepTime = dobaSpanku; //Doba spánku (ve vteřinách)
//Hodnoty pro práci s časem (Probuzení a kontrola času spánku)
static uint64_t sleep_start_us = 0;
struct timeval tv_now;
RTC_DATA_ATTR long int casSpankuStary; //hodnota ukládaná i přes deepSleep

void timeChecker() {  //Funkce pro kontrolu zda bylo zařízení ukradnuto
  sleep_start_us = gettimeofday(&tv_now,NULL);
  time_t now;
  time(&now);
  long int casSpanku = now

  if (casSpanku - casSpankuStary < sleepTime - 1)
  {
    kradez();
  }

  Serial.println();
  Serial.println("casSpanku:" + casSpanku);
  Serial.println("casSpankuStary" + casSpankuStary);
  casSpankuStary = casSpanku;
}

void kradez(){
  Serial.println("Ukradnuto");
}
void setup() {
  Serial.begin(9600);
}

void loop() {
  timeChecker();
  esp_deep_sleep(sleepTime * 1000000); //Uspání zařízení na dobu v proměné sleepTime
}