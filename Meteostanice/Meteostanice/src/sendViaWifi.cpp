#include <WiFi.h>
#include <HTTPClient.h>

#include <conf.h>

const char* ssid = "Jandourek";
const char* password = "hesloProNarusitele";

//Your Domain name with URL path or IP address with path
const String server_name = "http://207.180.232.51:8888";
const String server_data = "/novaData";
const String server_pohyb = "/kradez";

void setupWifiCon() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void sendDataViaWifi(float teplota, float vlhkost, int tlak, int co2, bool dest) {
    String teplota_text = String(teplota);
    String vlhkost_text = String(vlhkost);
    String tlak_text = String(tlak);
    String co2_text  = String(co2);
    String dest_text = String(dest);
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      String complete_adress = server_name + server_data;
      http.begin(complete_adress);
 
      http.addHeader("Content-Type", "application/json");
      String postBody = "{\"TEPLOTA\":\""+ teplota_text +"\", \"VLHKOST\":"+ vlhkost_text +", \"TLAK\":"+ tlak_text +", \"CO2\":"+ co2_text +", \"DEST\":"+ dest_text +"}";
      int httpResponseCode = http.POST(postBody);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}

void sendAlarmViaWifi(){
  //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      String complete_adress = server_name + server_pohyb;
      http.begin(complete_adress);
 
      http.addHeader("Content-Type", "application/json");
      String postBody = "{\"Pohyb\":\"1\"}";
      int httpResponseCode = http.POST(postBody);
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}