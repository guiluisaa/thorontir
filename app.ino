#define PIR 5 // GPIO05, Digital Pin D1
#define LED 4 // GPIO04, Digital Pin D2

#include <ESP8266WiFi.h>
const char *ssid = "ergil";        // SSID
const char *password = "senha123"; // password
const char *host = "www.handsontec.com";

void setup()
{
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

  delay(100);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  int trigger = digitalRead(PIR);

  if (trigger)
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  delay(500);
}