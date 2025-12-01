//
// Created by maksn on 17/11/2025.
//
#ifndef PROJECT_RIP_SENSOR_H
#define PROJECT_RIP_SENSOR_H

class RIP_Sensor {
    int pin;
public:
    RIP_Sensor(int pin);
    bool motionDetected() const;
    void waitForLow() const;
};


#endif