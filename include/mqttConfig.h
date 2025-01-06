#ifndef MQTT_CONFIG_H
#define MQTT_CONFIG_H

#include <MQTT.h>
#include "wifiConfig.h"
extern String mqttPayload;
const char *mqtt_broker = "msib7ldre.cloud.shiftr.io";
const int mqtt_port = 1883;
const char *mqtt_user = "msib7ldre";  // Username Shifter.io
const char *mqtt_pass = "bsimin1234"; // Password Shifter.io
WiFiClient net;
MQTTClient client;
String pathReceive = "uas/command";

void connectToMQTT()
{
    Serial.print("Menghubungkan ke broker MQTT...");
    while (!client.connect("client_id_esp8266", mqtt_user, mqtt_pass))
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("\nTerhubung ke broker MQTT!");
    client.subscribe(pathReceive);
    Serial.println("Subscribed ke topik: " + pathReceive);
}

void messageReceived(String &topic, String &payload)
{
    Serial.println("Pesan diterima: " + topic + " - " + payload);
    mqttPayload = payload;
    if (topic == pathReceive)
    {
        Serial.println("Data dari " + pathReceive + ": " + payload);
    }
    else
    {
        Serial.println("Topik tidak dikenali: " + topic);
    }
}

void setupMQTT()
{
    client.begin(mqtt_broker, mqtt_port, net); // Gunakan objek WiFiClient untuk MQTT
    client.onMessage(messageReceived);         // Set callback untuk pesan masuk
    connectToMQTT();
}

bool publishOneData(const String &data, const String &topic, int qos = 2)
{
    if (client.connected())
    {
        bool success = client.publish(topic, data, false, qos); // QoS ditentukan di sini
        if (success)
        {
            Serial.println("Data berhasil dikirim ke topik " + topic + ": " + data);
            return true;
        }
        else
        {
            Serial.println("Gagal mengirim data ke topik: " + topic);
            return false;
        }
    }
    else
    {
        Serial.println("Koneksi ke MQTT terputus, mencoba menyambungkan kembali...");
        connectToMQTT();
        return false;
    }
}

bool publishToMultipleTopics(const String &data1, const String &data2, const String &topic1, const String &topic2, int qos = 2)
{
    bool success1 = publishOneData(data1, topic1, qos);
    bool success2 = publishOneData(data2, topic2, qos);

    if (success1 && success2)
    {
        Serial.println("Data berhasil dikirim ke kedua topik.");
        return true;
    }
    else
    {
        Serial.println("Gagal mengirim data ke salah satu atau kedua topik.");
        return false;
    }
}

#endif
