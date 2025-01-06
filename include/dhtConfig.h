#ifndef DHT_CONFIG_H
#define DHT_CONFIG_H

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Define DHT pin and type
#define DHTPIN D3     // Pin where the DHT sensor is connected
#define DHTTYPE DHT11 // DHT 11 or DHT 22

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Function Prototypes
void setupDHT();
float getTemperature();
float getHumidity();

// Function Implementations
void setupDHT()
{
    dht.begin();
    Serial.println("DHT sensor initialized.");
}

float getTemperature()
{
    float temp = dht.readTemperature();
    if (isnan(temp))
    {
        // Serial.println("Failed to read temperature from DHT sensor!");
        return -999.0; // Return an error value
    }
    return temp;
}

float getHumidity()
{
    float humidity = dht.readHumidity();
    if (isnan(humidity))
    {
        // Serial.println("Failed to read humidity from DHT sensor!");
        return -999.0; // Return an error value
    }
    return humidity;
}

#endif // DHT_CONFIG_H
