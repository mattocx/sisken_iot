#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <Arduino.h>
#include "fanConfig.h"
#include "dhtConfig.h"
#include "lampConfig.h"
#include "mqttConfig.h"
// Array of valid commands
const String commands[] = {
    "nyalakan lampu.",
    "matikan lampu.",
    "nyalakan kipas.",
    "matikan kipas.",
    "set kipas sedang.",
    "set kipas maksimal.",
    "berapa suhu sekarang?",
    "berapa kelembaban sekarang?"};
const int commandCount = sizeof(commands) / sizeof(commands[0]);

void handleCommand(const String &command)
{
    if (command == "nyalakan lampu.")
    {
        // turnOnLamp(); // Call function to turn on the lamp
        Serial.println("Lampu dinyalakan.");
    }
    else if (command == "matikan lampu.")
    {
        // turnOffLamp(); // Call function to turn off the lamp
        Serial.println("Lampu dimatikan.");
    }
    else if (command == "nyalakan kipas.")
    {
        fanMax(); // Call function to turn on the fan at maximum speed
        Serial.println("kipas dinyalakan.");
    }
    else if (command == "matikan kipas.")
    {
        stopFan(); // Call function to stop the fan
        Serial.println("kipas dimatikan.");
    }
    else if (command == "set kipas sedang.")
    {
        fanMedium(); // Call function to set fan speed to medium
        Serial.println("kipas sedang.");
    }
    else if (command == "set kipas maksimal.")
    {
        fanMax(); // Call function to set fan speed to maximum
    }
    else if (command == "berapa suhu sekarang?")
    {
        float temperature = getTemperature();
        publishOneData(String(temperature), "uas/suhu");
        if (temperature != -999.0)
        {
            Serial.println("Suhu saat ini: " + String(temperature) + "°C");
        }
        else
        {
            Serial.println("Gagal membaca suhu.");
        }
    }
    else if (command == "berapa kelembaban sekarang?")
    {
        float humidity = getHumidity();
        publishOneData(String(humidity), "uas/kelembapan");
        if (humidity != -999.0)
        {
            Serial.println("Kelembapan saat ini: " + String(humidity) + "%");
        }
        else
        {
            Serial.println("Gagal membaca kelembapan.");
        }
    }
    else
    {
        Serial.println("Perintah tidak dikenali: " + command);
    }
}

bool isValidCommand(const String &command)
{
    for (int i = 0; i < commandCount; i++)
    {
        if (commands[i] == command)
        {
            return true;
        }
    }
    return false;
}

void processMQTTMessage(const String &message)
{
    if (!message.isEmpty())
    {
        if (isValidCommand(message))
        {
            handleCommand(message);
        }
        else
        {
            Serial.println("Pesan tidak valid: " + message);
        }
    }
    else
    {
        Serial.println("Pesan MQTT kosong.");
    }
}

#endif // COMMAND_HANDLER_H
