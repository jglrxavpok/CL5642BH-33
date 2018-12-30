#include "Arduino.h"
#include "CL5642BH_33.h"

// Pin mapping
uint8_t segA = 21; // ok
uint8_t segB = 17; // ok
uint8_t segC = 3; // ok
uint8_t segD = 5; // ok
uint8_t segE = 6; // ok
uint8_t dp = 4; // ok
uint8_t segF = 20; // ok

uint8_t digit1 = 22; // ok
uint8_t digit2 = 19; // ok
uint8_t digit3 = 18; // ok
uint8_t digit4 = 1; // ok
uint8_t segG = 2; // ok

CL5642BH_33* display = new CL5642BH_33(digit1, digit2, digit3, digit4, segA, segB, segC, segD, segE, segF, segG, dp);

String currentMessage = "ABCD";
uint8_t scrollOffset = 0;
long lastScrollTime = 0;

void setup() {
    display->setupPins();
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    display->glyphBuffer[0] = 'A';
    display->glyphBuffer[1] = 'A';
    display->glyphBuffer[2] = 'A';
    display->glyphBuffer[3] = 'A';

    digitalWrite(digit1, HIGH);
    digitalWrite(digit2, HIGH);
    digitalWrite(segA, LOW);

    SerialUSB.begin(9600);
    SerialUSB.println("Ready!");
}

void loop() {
    if(SerialUSB.available()) {
        String message = SerialUSB.readString(100);
        if(message) {
            currentMessage = message;
            scrollOffset = 0;
            SerialUSB.println(message);
            SerialUSB.printf("Received %s\n", message.c_str());
        }
    }
    if(millis()-lastScrollTime > 500) {
        scrollOffset++;
        lastScrollTime = millis();
    }

    display->glyphBuffer[0] = currentMessage.charAt(scrollOffset % currentMessage.length());
    display->glyphBuffer[1] = currentMessage.charAt((scrollOffset+1) % currentMessage.length());
    display->glyphBuffer[2] = currentMessage.charAt((scrollOffset+2) % currentMessage.length());
    display->glyphBuffer[3] = currentMessage.charAt((scrollOffset+3) % currentMessage.length());
    display->paintAsync();
    digitalWrite(13, LOW);
}
