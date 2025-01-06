#include <Arduino.h>
#include <dhtConfig.h>
#include <wifiConfig.h>
#include <ledConfig.h>
#include <mqttConfig.h>
#include <fanConfig.h>
#include "commandHandler.h"
unsigned long interval = 100;
unsigned long lastTime = 0;
String mqttPayload;
String pathSend = "uas/temperature";
String pathSend2 = "uas/humidity";
void setup()
{
  Serial.begin(115200);
  setupLEDs();
  setupDHT();
  setupFanControl();
  while (WiFi.status() != WL_CONNECTED)
  {
    connectToWiFi();
    turnOnLED_Red();
    if (WiFi.status() == WL_CONNECTED)
    {
      break;
    }
  }
  turnOnLED_Green();
  setupMQTT();
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Tidak Terkoneksi WiFi!");
    turnOnLED_Red();
    reconnectWiFi();
  }
  else
  {
    turnOnLED_Green();
  }
  if (!client.connected())
  {
    connectToMQTT();
  }
  if (millis() - lastTime >= interval)
  {
    lastTime = millis();
    float temperature = getTemperature();
    float humidity = getHumidity();
    publishToMultipleTopics(String(temperature), String(humidity), pathSend, pathSend2);
    processMQTTMessage(mqttPayload);
    mqttPayload = "";
  }
}