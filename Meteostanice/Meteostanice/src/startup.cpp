#include <Arduino.h>

/*!
 * @brief Zapnutí seriové komunikace
 * @param rychlost Rychlost seriové komunikace
 */
void zapniSerial(int rychlost){
    Serial.begin(rychlost);
    while (!Serial);
    Serial.println("");
}

/*!
 * @brief Zapnutí periferií (Připojení obvodu s moduly)
 */
void setupPorty(){
  pinMode(18, OUTPUT);
  digitalWrite(18,1);
}