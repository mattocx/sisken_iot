#ifndef FAN_CONTROL_H
#define FAN_CONTROL_H

#include <Arduino.h>

// Define L298N pins
#define ENA_PIN D5
#define IN1_PIN D6
#define IN2_PIN D7

// Function Prototypes
void setupFanControl();
void setFanSpeed(int speed); // Speed range: 0 to 255
void stopFan();
void fanMedium();
void fanMax();

// Function Implementations
void setupFanControl()
{
    pinMode(ENA_PIN, OUTPUT);
    pinMode(IN1_PIN, OUTPUT);
    pinMode(IN2_PIN, OUTPUT);
    stopFan(); // Ensure fan is stopped at initialization
}

void setFanSpeed(int speed)
{
    // if (speed < 0 || speed > 255)
    // {
    // Serial.println("Invalid speed value. Must be between 0 and 255.");
    //     return;
    // }

    digitalWrite(IN1_PIN, HIGH);
    digitalWrite(IN2_PIN, LOW);
    analogWrite(ENA_PIN, speed);
    // Serial.println("Fan speed set to: " + String(speed));
}

void stopFan()
{
    digitalWrite(IN1_PIN, LOW);
    digitalWrite(IN2_PIN, LOW);
    analogWrite(ENA_PIN, 0);
    Serial.println("Fan stopped.");
}

void fanMedium()
{
    setFanSpeed(150);
    Serial.println("Fan set to medium speed (150).");
}

void fanMax()
{
    setFanSpeed(255);
    Serial.println("Fan set to maximum speed (255).");
}

#endif // FAN_CONTROL_H
