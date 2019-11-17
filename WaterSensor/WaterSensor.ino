#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "AndroidAPAF67";
const char* password = "ioei9326";

void setup () {
  Serial.begin(115200);
  Serial.println("Started.");
  WiFi.begin(ssid, password);
 
  connect();
}
 
void loop() {
  int value = analogRead(A0);
}

void connect()
{
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }

  Serial.println("Connected.");
}
