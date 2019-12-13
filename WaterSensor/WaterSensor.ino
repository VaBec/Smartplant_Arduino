#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void connect();

// WeMos D1 R2 & mini

const char* ssid = "SchnauzePuppe";
const char* password = "78131887303241935007";

//const char* ssid = "AndroidAPAF67";
//const char* password = "ioei9326";
 
void setup () {
  pinMode(D1, OUTPUT);

  for(int i=0 ; i<50 ; i++)
  {
    digitalWrite(D1, HIGH);
    delay(10);
    digitalWrite(D1, LOW);
    delay(10);
  }

  Serial.begin(115200);
  Serial.println("Started.");
  WiFi.begin(ssid, password);
 
  connect();
}
 
void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("####################################");
    Serial.println("Connected");

    sendPlantData();
    waterIfNeeded();
    
    Serial.println("####################################");
    Serial.println("");
    delay(5000);
  } else {
    Serial.println("Connection lost. Reconnecting.");
    connect();
  }
}

void waterIfNeeded()
{
  String mac = WiFi.macAddress();
  String payload;

  HTTPClient http;
  
  http.begin("http://smartplant.azurewebsites.net/get");
  http.addHeader("Content-Type", "application/json");

  payload += "{\"macAddress\":\"";
  payload +=  mac;
  payload += "\"}";

  int httpCode = http.sendRequest("POST", payload);

  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);

    if(payload.indexOf("\"payload\":true") > 0) {
      Serial.println("Watering!");
      digitalWrite(D1, HIGH);
      delay(1000);
      digitalWrite(D1, LOW);
    } else {
      Serial.println("Not watering!");
    }
  } else {
    Serial.println(httpCode);
  }
  
  http.end();
}

void sendPlantData()
{
  String mac = WiFi.macAddress();
  String payload;

  HTTPClient http;
  
  http.begin("http://smartplant.azurewebsites.net/updateplant");
  http.addHeader("Content-Type", "application/json");

  int value = analogRead(A0);

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
  
  http.end();
}

void connect()
{
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
}

