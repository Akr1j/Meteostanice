# Senzor deště
## Propojení
|ESP|Modul deště|
|-------|----------|
|5V|VCC|
|GND|GND|
|D0|P34|
|A0|-|

## Funkce
V případě deště (namočení senzorové plochy) ukládá do proměné "bIsRaining" hodnotu 1. Tato hodnota je vypisována do konzole.
## Poznámky
- Může být aktivováno vlhkostí či jinými vnějšímy vlivy
- Odesílá signál o dešti i v případě že již neprší ale senzor je stále mokrý/vlhký

## Zdroje
[Rain Sensor Tutorial for Arduino, ESP8266 and ESP32](https://diyi0t.com/rain-sensor-tutorial-for-arduino-and-esp8266/)