#include <WiFi.h>
#include <HTTPClient.h>

/*!
* @brief Připojení se do WIFI sítě
* @param ssid Název sítě do které se má zařízení připojit
* @param password Heslo sítě do které se má zařízení připojit
*/
void setupWifiCon(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  int pocet_pokusu_o_pripojeni = 0;
  while(WiFi.status() != WL_CONNECTED || pocet_pokusu_o_pripojeni < 50) {
    delay(500);
    Serial.print(".");
    pocet_pokusu_o_pripojeni++;
  }
  if (pocet_pokusu_o_pripojeni < 50)
  {
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
  }else
  {
    Serial.println("Chyba připojení k WIFI");
    esp_restart();
  }
}

/*!
 * @brief Odeslání dat na server pomocí WIFI
 * @param adresa Adresa na kterou se data mají posílat
 * @param teplota Hodnota teploty odesílaná na server
 * @param vlhkost Hodnota vlhkosti odesílaná na server
 * @param tlak Hodnota tlaku odesílaná na server
 * @param co2 Hodnota CO2 odesílaná na server
 * @param dest Hodnota zobrazující zda prší odesílaná na server
 */
void sendDataViaWifi(const char* adresa, float teplota, float vlhkost, int tlak, int co2, bool dest) {
  String teplota_text = String(teplota);
  String vlhkost_text = String(vlhkost);
  String tlak_text = String(tlak);
  String co2_text  = String(co2);
  String dest_text = String(dest);
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HTTPClient http;
    http.begin(adresa);
    http.addHeader("Content-Type", "application/json");
    String postBody = "{\"TEPLOTA\":\""+ teplota_text +"\", \"VLHKOST\":"+ vlhkost_text +", \"TLAK\":"+ tlak_text +", \"CO2\":"+ co2_text +", \"DEST\":"+ dest_text +"}";
    int httpResponseCode = http.POST(postBody);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
    esp_restart();
  }
}

/*!
 * @brief Odeslání oznámení o ukradnutí
 * @param adresa Adresa na kterou se mají data posílat
 */
void sendDataViaWifi(const char* adresa){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HTTPClient http;
    http.begin(adresa);
    http.addHeader("Content-Type", "application/json");
    String postBody = "{\"Pohyb\":\"1\"}";
    int httpResponseCode = http.POST(postBody);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
    esp_restart();
  }
}

/*!
 * @brief Odesílání oznámení o chybách
 * @param adresa Adresa na kterou se mají data posílat
 * @param id id chyby
 * @param zaznam popis chyby
 */
void sendDataViaWifi(const char* adresa, int id,const char* zaznam){
    String id_text = String(id);
    String zaznam_text = String(zaznam);
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HTTPClient http;
    http.begin(adresa);
    http.addHeader("Content-Type", "application/json");
    String postBody = "{\"ID\":\""+ id_text +"\", \"ZAZNAM\":"+ zaznam_text +", \"MISTO\":\"Meteo1\"}";
    int httpResponseCode = http.POST(postBody);
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
    esp_restart();
  }
}