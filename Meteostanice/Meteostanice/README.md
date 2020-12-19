# Zabezpečení krádeže
```
static uint64_t sleep_start_us = 0;
struct timeval tv_now;

void timeChecker() {
  sleep_start_us = gettimeofday(&tv_now,NULL);
  time_t now;
  time(&now);
  printf(ctime(&now));
}
```

# Zdroje
## Uspání
[System Time](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html)
[[C/C++] Converting time structure to date format](https://ubuntuforums.org/archive/index.php/t-1114250.html)

## Senzor deště
[Rain Sensor Tutorial for Arduino, ESP8266 and ESP32](https://diyi0t.com/rain-sensor-tutorial-for-arduino-and-esp8266/)


# Pokud se nejde dostat na port
sudo chmod a+rw /dev/ttyUSB0

# Prozatimní rozložení portů

|ESP|senzory|
|---|--|
|P34|RAINDROP(D0 - asi)|
|EN|Senzor otřesů D0|