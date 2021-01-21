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
 * @brief Zapnití periferií
 */
void setupPorty(){
  pinMode(5, OUTPUT);
  digitalWrite(5,1);
}