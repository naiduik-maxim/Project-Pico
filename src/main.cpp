#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID "TOTOLINK N150RT"
#define WIFI_PASS "029113qweASD"
String serverUrl = "http://192.168.1.10:5000/report_motion";

#include "RIP_Sensor.h"
#define ADOPT_TIME 30

RIP_Sensor AM132(16);

void setup() {
    Serial.begin(115200);

    Serial.println();
    Serial.print("Connecting to WiFi");
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    Serial.println("RIP Sensor Demo, waiting 30 seconds for adapting...");
    delay(ADOPT_TIME * 1000);
    Serial.println("RIP Sensor Demo ready for working");
}

void loop() {
    if (AM132.motionDetected()) {
        Serial.println("RIP Sensor see motion! Sending signal...");

        if (WiFi.status() == WL_CONNECTED) {
            HTTPClient http;
            http.setTimeout(5000);

            http.begin(serverUrl);

            int httpCode = http.POST("");

            if (httpCode > 0) {
                Serial.printf("Server notified. Response: %d\n", httpCode);
            } else {
                Serial.printf("Error reaching server: %s\n", http.errorToString(httpCode).c_str());
            }

            http.end();
        } else {
            Serial.println("WiFi Disconnected!");
        }
        delay(10000);
        Serial.println("Ready for next motion...");

    } else {
        delay(100);
    }
}