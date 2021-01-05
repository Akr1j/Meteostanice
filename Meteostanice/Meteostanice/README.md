# Obsah
[Limity projektu](#Limity-projektu)<br>
[Zabezpečení krádeže](#Zabezpečení-krádeže)
# Limity projektu
||Teplota|Tlak|CO2|
|--|-----|---|--|
|Maximum|50|110000|8192|
|Minimum|-20|30000|400|

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
- [System Time](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/system_time.html)
- [[C/C++] Converting time structure to date format](https://ubuntuforums.org/archive/index.php/t-1114250.html)

## Senzor deště
- [Rain Sensor Tutorial for Arduino, ESP8266 and ESP32](https://diyi0t.com/rain-sensor-tutorial-for-arduino-and-esp8266/)

## BMP senzor
- [ESP32 and BMP280 sensor example](http://www.esp32learning.com/code/esp32-and-bmp280-sensor-example.php)
- [Adafruit BMP280 Driver](https://github.com/adafruit/Adafruit_BMP280_Library)
- [ESP32 with BME280 Sensor using Arduino IDE (Pressure, Temperature, Humidity)](https://randomnerdtutorials.com/esp32-bme280-arduino-ide-pressure-temperature-humidity/)
- [Oficiální dokumentace](https://www.bosch-sensortec.com/products/environmental-sensors/pressure-sensors/pressure-sensors-bmp280-1.html) 
  - a na tomto odkazu nelezený [Data sheet](https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmp280-ds001.pdf)

## CO2 senzor
- [TVOC and CO2 Measurement using Arduino and CCS811 Air Quality Sensor](https://circuitdigest.com/microcontroller-projects/tvoc-co2-measurement-using-aduino-and-ccs811-air-quality-sensor)
- [Oficiální dokumentace](https://cdn.sparkfun.com/assets/learn_tutorials/1/4/3/CCS811_Datasheet-DS000459.pdf)


## Wifi
- [ESP32 HTTP GET and HTTP POST](https://randomnerdtutorials.com/esp32-http-get-post-arduino/#http-post)

## Technika kódu
- [Refaktorování](https://cs.wikipedia.org/wiki/Refaktorov%C3%A1n%C3%AD)


# Pokud se nejde dostat na port
sudo chmod a+rw /dev/ttyUSB0

# (Prozatimní) Zapojení

![Zapojení](Meteostanice_bb.png)

# Mohlo by se hodit
[I2C komunikace](https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/)