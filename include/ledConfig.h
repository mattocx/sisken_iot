#ifndef LED_CONFIG_H
#define LED_CONFIG_H

#include <Arduino.h>

// Pin Definitions
#define LED_PIN_Red D2
#define LED_PIN_Green D1

// Function Prototypes
void setupLEDs();
void turnOnLED_Red();
void turnOnLED_Green();
void turnOnBothLEDs();
void turnOffLEDs();

// Function Implementations
void setupLEDs()
{
    pinMode(LED_PIN_Red, OUTPUT);
    pinMode(LED_PIN_Green, OUTPUT);
}

void turnOnLED_Red()
{
    digitalWrite(LED_PIN_Red, HIGH);
    digitalWrite(LED_PIN_Green, LOW);
}

void turnOnLED_Green()
{
    digitalWrite(LED_PIN_Red, LOW);
    digitalWrite(LED_PIN_Green, HIGH);
}

void turnOffLEDs()
{
    digitalWrite(LED_PIN_Red, LOW);
    digitalWrite(LED_PIN_Green, LOW);
}

#endif
