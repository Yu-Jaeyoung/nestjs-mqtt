#include <ArduinoHttpClient.h>
#include <WiFiNINA.h>
#include <PubSubClient.h>

// WiFi
const char* ssid = "Hanbat_WLAN_Guest";  // Enter your WiFi name
const char* password = "";               // Enter WiFi password

WiFiClient espClient;
PubSubClient client(espClient);

// MQTT Broker
const char* mqtt_server = "broker.emqx.io";  // Enter your WiFi or Ethernet IP
const int mqtt_port = 1883;
const char* topic = "stevia-mqtt";

// Button & Solenoid
int buttonPin = 4; // Button Pin
int solenoidPin = 8; // Solenoid Pin

#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

void setup() {
  Serial.begin(9600);

  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  
  pinMode(buttonPin, INPUT);
  pinMode(solenoidPin, OUTPUT);
}

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    if (client.connect("stevia")) {
      Serial.println("connected");
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");

  String command = "";
  for (int i = 0; i < length; i++) {
    command += (char)payload[i];
  }
  Serial.println(command);

  if (command.equals("ON") || command.equals("on") || command.equals("On")) {
    digitalWrite(solenoidPin, HIGH); // 스위치를 누른 상태로 설정
    Serial.println("Button Pressed - Solenoid On"); // 시리얼 모니터에 메시지 출력
    delay(2000);
    digitalWrite(solenoidPin, LOW); // 스위치를 누르지 않은 상태로 설정
    snprintf(msg, 50, "Open");
		client.publish(topic, msg);
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();
  
}
