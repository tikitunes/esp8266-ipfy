#include <ESP8266WiFi.h>

const char *ssid = "";
const char *password = "";

void setup() {
  Serial.begin(115200);
  Serial.println();
  configWiFi();
  Serial.println(getPublicIP());
}

void loop() {
  delay(1000 * 5);
}

void configWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
  }
}
String getPublicIP() {
  WiFiClient client;
  String host = "api.ipify.org";
  String url = "/";
  int port = 80;
  String PublicIP = "";

  if (!client.connect(host, 80)) {
    return "connection failed";
  }
  client.print(String("GET ") + url + 
               " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

  // read headers
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }

  // api.ipify.org will return ip address as text
  char c;
  int size = 0;
  while (client.connected()) {
    while ((size = client.available()) > 0) {
      c = client.read();
      PublicIP += c;
    }
  }
  return PublicIP;
}
