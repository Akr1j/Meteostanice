#include <WiFi.h>
#include <HTTPClient.h>
#include <conf.h>
#include <spanek.h>

/*!
* @brief Připojení se do WiFi sítě
* @return 0 pokud chyba
*/
bool setupWifiCon() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  int pocet_pokusu_o_pripojeni = 0;
  while(WiFi.status() != WL_CONNECTED && pocet_pokusu_o_pripojeni < 50) {
    delay(500);
    Serial.print(".");
    pocet_pokusu_o_pripojeni++;
  }
  if (pocet_pokusu_o_pripojeni < 50)
  {
    Serial.println("");
    Serial.print("Connected to WiFi network with IP Address: ");
    Serial.println(WiFi.localIP());
    return 0;
  }else
  {
    Serial.println("Chyba připojení k WIFI");
    usni(900);
    return 1;
  }
}

/*!
 * @brief Odeslání dat na server pomocí WiFi
 * @param teplota Hodnota teploty k odesílání na server
 * @param vlhkost Hodnota vlhkosti k odesílání na server
 * @param tlak Hodnota tlaku k odesílání na server
 * @param co2 Hodnota CO2 k odesílání na server
 * @param dest Hodnota zobrazující zda prší k odesílání na server
 */
void sendDataViaWifi(float teplota, float vlhkost, int tlak, int co2, bool dest) {
  String teplota_text = String(teplota);
  String vlhkost_text = String(vlhkost);
  String tlak_text = String(tlak);
  String co2_text  = String(co2);
  String dest_text = String(dest);

  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HTTPClient http;
    http.begin(server_data); //server_data - adresa API serveru pro zaznamenání dat
    http.addHeader("Content-Type", "application/json");
    
    String postBody = "{\"TEPLOTA\":\""+ teplota_text +"\", \"VLHKOST\":"+ vlhkost_text +", \"TLAK\":"+ tlak_text +", \"CO2\":"+ co2_text +", \"DEST\":"+ dest_text +"}";
    Serial.print("Odesláno: Teplota:");
      Serial.print(teplota_text);
      Serial.print(", Vlhkost:");
      Serial.print(vlhkost_text);
      Serial.print(", Tlak:");
      Serial.print(tlak_text);
      Serial.print(", CO2:");
      Serial.print(co2_text);
      Serial.print(", Dest:");
      Serial.println(dest_text);
    
    int httpResponseCode = http.POST(postBody);
    Serial.print("HTTP Response code pro /novaData: ");
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
 */
void sendDataViaWifi(){
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HTTPClient http;
    http.begin(server_pohyb); //server_pohyb - adresa API serveru pro zaznamenání pohybu
    http.addHeader("Content-Type", "application/json");
    
    String postBody = "{\"Pohyb\":\"1\"}";
    
    int httpResponseCode = http.POST(postBody);
    Serial.print("HTTP Response code pro /pohyb: ");
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
 * @param idChyby id chyby
 * @param zaznam popis chyby
 */
void sendDataViaWifi(int idChyby,const char* zaznam){
    String idChyby_text = String(idChyby);
    String zaznam_text = String(zaznam);
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
    HTTPClient http;
    http.begin(server_error); //server_error - adresa API serveru pro zaznamenání chyb
    http.addHeader("Content-Type", "application/json");

    String postBody = "{\"ID\":\""+ idChyby_text +"\", \"ZAZNAM\":\""+ zaznam_text +"\", \"MISTO\":\"Meteo1\"}";

    int httpResponseCode = http.POST(postBody);
    Serial.print("HTTP Response code pro /chyba: ");
      Serial.println(httpResponseCode);
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
    esp_restart();
  }
}