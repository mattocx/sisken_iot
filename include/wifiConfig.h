#ifndef WIFI_CONFIG_H
#define WIFI_CONFIG_H

#include <WiFiManager.h>
WiFiManager wm;

void connectToWiFi()
{
    Serial.println("Trying to connect to saved WiFi...");
    wm.setConnectTimeout(30);
    wm.autoConnect("ESP-Uas") ? Serial.println("Connected to WiFi!") : Serial.println("Failed to connect to WiFi.");
}

void reconnectWiFi()
{
    unsigned long startMillis = millis();
    unsigned long timeout = 30000;

    while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.reconnect();
        delay(500);
        if (WiFi.status() == WL_CONNECTED)
        {
            break;
        }
        else if (millis() - startMillis >= timeout)
        {
            Serial.println("Failed to reconnect within 10 seconds.");
            break;
        }
    }
    WiFi.status() == WL_CONNECTED ? Serial.println("Reconnected to WiFi!") : wm.autoConnect("ESP-Reconnect UAS");
}

#endif
