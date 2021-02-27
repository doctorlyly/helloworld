/*
* Time:20200508
* Author: youngda
* QQ:1217882800
* wechat:19092550573
* QQ竤824273231
* ?ヘボㄒ硄?塝癳on┪off北??
*/
#include<Arduino.h>
//#include <ESP8266WiFi.h>//纐??WIFI塦ゅン
#include <WiFi.h>
#include "PubSubClient.h"//纐??MQTT?ゅン

const char* ssid = "CMCC-iupx";//э隔パWIFI
const char* password = "k7ffd9wp";//WIFI盞?
const char* mqtt_server = "bemfa.com";//纐?MQTT狝塙竟
const int mqtt_server_port = 9501;//纐?MQTT狝塙竟
#define ID_MQTT  "43dc97ed0846e284e02843f0eed27301"     //эClient ID
const char*  topic = "light001";  //?ぺ猭お北︽??曭種


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//嶘ㄧ?のま庎﹚
void turnOnLed();
void turnOffLed();
const int B_led = 2;


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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String Mqtt_Buff = "";
  for (int i = 0; i < length; i++) {
    Mqtt_Buff += (char)payload[i];
  }
  Serial.print(Mqtt_Buff);
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if (Mqtt_Buff == "on") {//狦钡Μ才on獹嶘
    turnOnLed();//?嶘ㄧ?

  } else if (Mqtt_Buff == "off") {//狦钡Μ才off獹嶘
    turnOffLed();//?嶘ㄧ?
  }
  Mqtt_Buff = "";
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(ID_MQTT)) {
      Serial.println("connected");

      client.subscribe(topic);//ээ??
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup() {
  pinMode(B_led, OUTPUT);

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_server_port);
  client.setCallback(callback);
  digitalWrite(B_led, HIGH);
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}

//ゴ?嶘獁
void turnOnLed() {
  Serial.println("turn on light");
  digitalWrite(B_led, LOW);
}
//??嶘獁
void turnOffLed() {
    Serial.println("turn off light");
  digitalWrite(B_led, HIGH);
}
