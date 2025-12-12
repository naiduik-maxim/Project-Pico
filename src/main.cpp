#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID "*********"
#define WIFI_PASS "*********"

String serverName = "*************";
const int port = 0;
String serverUrl = "report_motion";

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

    Serial.println("Wait 30 second for adapting...");
    delay(ADOPT_TIME * 1000);
    Serial.println("RIP Sensor working");
}

void loop() {
    if (AM132.motionDetected()) {
        Serial.println("RIP Sensor see motion!");

        if (WiFi.status() == WL_CONNECTED) {
            HTTPClient http;
            http.setTimeout(5000);

            String checkURL = "http://" + serverName + ":" + String(port) + "/" + serverUrl;

            http.begin(checkURL);

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
        Serial.println("Ready for next motion!");

    } else {
        delay(100);
    }
}