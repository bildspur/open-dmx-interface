#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

#include "Adafruit_LEDBackpack.h"

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

// serial
#define BAUD_RATE 115200

char displaybuffer[4] = {' ', ' ', ' ', ' '};

// variable
void setup() {
    Serial.begin(BAUD_RATE);

    // wait 3000 seconds for debugging
    delay(3000);

    // setup wire
    Wire.begin(D2, D1);

    alpha4.begin(0x70);  // pass in the address

    alpha4.clear();
    alpha4.writeDisplay();

    // display every character,
    for (uint8_t i='!'; i<='z'; i++) {
        alpha4.writeDigitAscii(0, i);
        alpha4.writeDigitAscii(1, i+1);
        alpha4.writeDigitAscii(2, i+2);
        alpha4.writeDigitAscii(3, i+3);
        alpha4.writeDisplay();

        delay(300);
    }
    Serial.println("Start typing to display!");

    Serial.println("setup finished!");
}

void loop() {
    while (! Serial.available()) return;

    char c = Serial.read();
    if (! isprint(c)) return; // only printable!

    // scroll down display
    displaybuffer[0] = displaybuffer[1];
    displaybuffer[1] = displaybuffer[2];
    displaybuffer[2] = displaybuffer[3];
    displaybuffer[3] = c;

    // set every digit to the buffer
    alpha4.writeDigitAscii(0, displaybuffer[0]);
    alpha4.writeDigitAscii(1, displaybuffer[1]);
    alpha4.writeDigitAscii(2, displaybuffer[2]);
    alpha4.writeDigitAscii(3, displaybuffer[3]);

    // write it out!
    alpha4.writeDisplay();
    delay(200);
}