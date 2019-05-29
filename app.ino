#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define PIR 5 // GPIO05, Digital Pin D1
#define LED 4 // GPIO04, Digital Pin D2

const char* ssid = "ergil";        // SSID
const char* password = "senha123"; // password

const char* mqtt_server = "iot.eclipse.org";
const int mqtt_port = 1883;


const char* mqtt_client_id = "ESP8266-Thorontir";

WiFiClient node_client;
PubSubClient client(node_client);

const char* movementTopic = "thorontir/movement";
const char* allowLedTopic = "thorontir/allow-led";

int hasSomeone = LOW;
int allowLed = LOW;

void setup() {
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

  delay(100);

  Serial.println();
  Serial.println();
  
  connectWiFi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  client.subscribe(allowLedTopic, true);
}

void loop() {
  client.loop();

  if (!client.connected()) {
    reconnect();
  }

  int trigger = digitalRead(PIR);

  if (trigger) {
    digitalWrite(LED, HIGH);
    if(hasSomeone == LOW) {
      handleMovement(hasSomeone);
      hasSomeone = HIGH;
    }
  } else {
    digitalWrite(LED, LOW);
    if(hasSomeone == HIGH) {
      handleMovement(hasSomeone);
      hasSomeone = LOW;
    }
  }
  
  delay(500);
}

void connectWiFi() {
  delay(10);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    client.connect(mqtt_client_id);
  }
}

void handleMovement(int isMoving) {
  if (!isMoving) {
    client.publish(movementTopic, "Movement detected", true);
    Serial.println("Start Moving");
  } else {
    client.publish(movementTopic, "No movement detected", true);
    Serial.println("Stop Moving");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message: ");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}