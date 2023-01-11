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
  sendJsonToAWS();
  client.loop();
  delay(1000);
}
