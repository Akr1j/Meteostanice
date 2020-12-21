#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Jandourek";
const char* password = "hesloProNarusitele";

//Your Domain name with URL path or IP address with path
const std::string server_name = "http://207.180.232.51:8888";
const std::string server_data = "/novaData";
const std::string server_pohyb = "/kradez";

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

void sendDataViaWifi(int teplota, int vlhkost, int tlak, int co2, bool dest) {
    String teplota_text = String(teplota);
    String vlhkost_text = String(vlhkost);
    String tlak_text = String(tlak);
    String co2_text  = String(co2);
    String dest_text = String(dest);

    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      std::string complete_adress = server_name + server_data;
      const char *urlAdress = complete_adress.c_str();
      http.begin(urlAdress);
 
      http.addHeader("Content-Type", "application/json");
      String postBody = "{\"CAS\":\"2020-12-19 12:00:00\", \"TEPLOTA\":\""+ teplota_text +"\", \"VLHKOST\":"+ vlhkost_text +", \"TLAK\":"+ tlak_text +", \"CO2\":"+ co2_text +", \"DEST\":"+ dest_text +"}";
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
      std::string complete_adress = server_name + server_pohyb;
      const char *urlAdress = complete_adress.c_str();
      http.begin(urlAdress);
 
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