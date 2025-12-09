//
// Created by maksn on 17/11/2025.
//

#include "RIP_Sensor.h"
#include <Arduino.h>

RIP_Sensor::RIP_Sensor(int pin) : pin(pin) {
    pinMode(pin, INPUT_PULLDOWN);
}

bool RIP_Sensor::motionDetected() const {
    Serial.print(digitalRead(pin) == HIGH);
    return digitalRead(pin) == HIGH;
}

void RIP_Sensor::waitForLow() const {
    while (digitalRead(pin) == HIGH) delay(100);
}

