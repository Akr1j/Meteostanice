#include <WiFi.h>
#include <sendingDataViaWiFi/sendViaWifi.h>

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

bool i = setupWifiCon();