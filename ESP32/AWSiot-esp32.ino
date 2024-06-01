#include "certs.h"
#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include "WiFi.h"

const char *WIFI_SSID = "*****";
const char *WIFI_PASSWORD = "******";

#define DEVICE_NAME "my-arduino-device"

#define AWS_IOT_ENDPOINT "xxxxxxxxxxx.iot.eu-west-1.amazonaws.com"

#define AWS_IOT_TOPIC "$aws/things/" DEVICE_NAME "/shadow/update"

#define AWS_MAX_RECONNECT_TRIES 50

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);

void setup() {
  Serial.begin(9600);
  connectToWiFi();
  connectToAWS();
}
void loop() {
 StaticJsonDocument<128> jsonDoc;
  JsonObject stateObj = jsonDoc.createNestedObject("state");
  JsonObject reportedObj = stateObj.createNestedObject("reported");
  
  reportedObj["temperature"] = 23.76;
  reportedObj["humidity"] = 78.12;
  reportedObj["wifi_strength"] = WiFi.RSSI();

  JsonObject locationObj = reportedObj.createNestedObject("location");
  locationObj["name"] = "Garden";

  Serial.println("Publishing message to AWS...");
  //serializeJson(doc, Serial);
  char jsonBuffer[512];
  serializeJson(jsonDoc, jsonBuffer);

  client.publish(AWS_IOT_TOPIC, jsonBuffer);
  client.loop();
  delay(1000);
}
