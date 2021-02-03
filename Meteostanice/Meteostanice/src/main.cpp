#include <spanek.h>
#include <senzory.h>
#include <startup.h>
#include <sendViaWifi.h>

const int sleepTime = 30; //Doba spánku (ve vteřinách)
#define rozptylCasu 1 //Rozsah korekce času (časovač se posunuje. Zde doba kdy se vyhlásí poplach)

const int pin_pro_dest = 34; //Port pro připojení senzoru deště

bool err_bmp280;
float data_BMP;

void setup() {
  zapniSerial(9600);
  timeChecker(sleepTime, rozptylCasu);
  setupPorty();
  err_bmp280 = setupBMP280();
  setupCCS811();
  setupDestSenzor(pin_pro_dest);
  setupWifiCon();
  data_BMP = 50; //Defaultní hodnota (V případě chyby)
  tlak = 0; //Defaultní hodnota (V případě chyby)
}

void loop() {
  bool zda_prsi = isPrsi(pin_pro_dest);
  
  if (!err_bmp280)
    data_BMP = readValueBMP280();

  int co2 = readValueCCS811();

  sendDataViaWifi(data_BMP, 0, tlak, co2, zda_prsi);
  usni(sleepTime);
}