#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void connect();

// WeMos D1 R2 & mini

const char* ssid = "SchnauzePuppe";
const char* password = "78131887303241935007";

//const char* ssid = "AndroidAPAF67";
//const char* password = "ioei9326";
 
void setup () {
  Serial.begin(115200);
  Serial.println("Started.");
  WiFi.begin(ssid, password);
 
  connect();
}
 
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("####################################");
    Serial.println("Connected");

    HTTPClient http;
     
    http.begin("http://smartplant.azurewebsites.net/updateplant");
    http.addHeader("Content-Type", "application/json");

    int value = analogRead(A0);
    String mac = WiFi.macAddress();

    String payload;

    payload += "{\"macAddress\":\"";
    payload +=  mac;
    payload += "\",\"watervalue\":\"";
    payload += String(value);
    payload += "\",\"owner\":\"";
    payload += "Momo";
    payload += "\",\"planttype\":\"";
    payload += String(0);
    payload += "\"}";
    
    Serial.println(payload);
        
    int httpCode = http.sendRequest("PUT", payload);
     
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      Serial.println(httpCode);
    }

    Serial.println("####################################");
    Serial.println("");
   
    http.end();
    delay(1000);
  } else {
    Serial.println("Connection lost. Reconnecting.");
    connect();
  }
}

void connect()
{
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
}

