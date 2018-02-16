#include <Arduino.h>
#include <Wire.h>

// serial
#define BAUD_RATE 115200

// variable
void setup() {
    Serial.begin(BAUD_RATE);

    // wait 3000 seconds for debugging
    delay(3000);

    // setup wire
    Wire.begin(D2, D1);

    Serial.println("setup finished!");
}

void loop() {
}