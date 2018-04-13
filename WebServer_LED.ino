#include<ESP8266WiFi.h>

const char * ssid = "Yashwanth";
const char * pass = "123556789";

WiFiServer server(80);
int led = 5;
String header;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  WiFi.begin(ssid, pass);
  Serial.println("Connecting...");
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }
  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);Serial.println();
  Serial.print("Connected to "); Serial.println(ssid);
  Serial.print("Local IP: "); Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    client.println("ESP8266");
    while(client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (header.indexOf("GET /5/on") != -1) {
            Serial.println("LED 5: ON");
            client.write("LED 5: ON");
            digitalWrite(led, HIGH);
            header = "";
          } else if (header.indexOf("GET /5/off") != -1) {
            Serial.println("LED 5: OFF");
            client.write("LED 5: OFF");
            digitalWrite(led, LOW);            
            header = "";
          }
          
        }
      }
    }
  client.stop();
  Serial.println();
  Serial.println("Client Disconnected");
  Serial.println();
  }

}
