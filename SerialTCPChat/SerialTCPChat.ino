
#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "HOTBOX2020"
#define STAPSK  "10203040"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

WiFiServer server(8080);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if(!client)
  {
    return;
  }
  Serial.println("Received connection !");
  while(client.connected())
  {
    while(client.available())
    {
      char c = client.read();
      Serial.print(c);
    }
    client.flush();
    while(Serial.available())
    {
      char c = Serial.read();
      client.print(c);
    }
  }
  
  
}
