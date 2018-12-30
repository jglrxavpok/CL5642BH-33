//
// Created by jglrxavpok on 29/12/18.
//

// http://www.hobbytronics.co.uk/arduino-4digit-7segment
// https://i.stack.imgur.com/RUUEq.png
#include "glyphs.h"
#include <core_pins.h>
#include <ctype.h>
#include <usb_serial.h>
#include "CL5642BH_33.h"

int sign(long number) {
    if(number > 0)
        return 1;
    else if(number < 0)
        return -1;
    return 0;
}

CL5642BH_33::CL5642BH_33(uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4, uint8_t segmentA,
                         uint8_t segmentB, uint8_t segmentC, uint8_t segmentD, uint8_t segmentE, uint8_t segmentF,
                         uint8_t segmentG, uint8_t digitalPoint): digit1(digit1), digit2(digit2), digit3(digit3), digit4(digit4),
                         segmentA(segmentA), segmentB(segmentB), segmentC(segmentC), segmentD(segmentD), segmentE(segmentE), segmentF(segmentF), segmentG(segmentG),
                         digitalPoint(digitalPoint) {
    initArrays();
}

void CL5642BH_33::initArrays() {
    digitPins[0] = digit1;
    digitPins[1] = digit2;
    digitPins[2] = digit3;
    digitPins[3] = digit4;

    segmentPins[0] = segmentA;
    segmentPins[1] = segmentB;
    segmentPins[2] = segmentC;
    segmentPins[3] = segmentD;
    segmentPins[4] = segmentE;
    segmentPins[5] = segmentF;
    segmentPins[6] = segmentG;

    initDefaultGlyphTable(glyphs);
}

void CL5642BH_33::paint() {
    long beginTime = millis();
    paintAsync();
    while((millis()-beginTime) < 10); // wait for 10ms to have passed
}

void CL5642BH_33::paintAsync() {
    static long lastCallTime = 0;
    if(millis()-lastCallTime >= 10) {
        for(uint8_t currentDigit = 0; currentDigit < 4; currentDigit++) {
            // light up only the current digit
            for (uint8_t digit = 0; digit < 4; digit++) {
                digitalWrite(digitPins[digit], (uint8_t)(digit == currentDigit ? DIGIT_ON : DIGIT_OFF));
            }

            drawCharacter(glyphBuffer[currentDigit]);

            switch(currentDigit) {
                case 0:
                    digitalWrite(digitalPoint, (uint8_t)(digitalPoints[1] ? SEGMENT_ON : SEGMENT_OFF));
                    break;

                case 1:
                    digitalWrite(digitalPoint, (uint8_t)(lightUpColon ? SEGMENT_ON : SEGMENT_OFF));
                    break;

                case 2:
                    digitalWrite(digitalPoint, (uint8_t)(digitalPoints[2] ? SEGMENT_ON : SEGMENT_OFF));
                    break;

                case 3:
                    digitalWrite(digitalPoint, (uint8_t)(digitalPoints[3] ? SEGMENT_ON : SEGMENT_OFF));
                    break;
            }

            delayMicroseconds(DISPLAY_BRIGHTNESS);
            clearCharacter();
            digitalWrite(digitPins[currentDigit], DIGIT_OFF);
        }
        lastCallTime = millis();
    }
}

void CL5642BH_33::clearCharacter() {
    for(uint8_t segment = 0; segment <= 7; segment++)
        digitalWrite(segmentPins[segment], SEGMENT_OFF);
}

void CL5642BH_33::drawCharacter(char c) {
    uint8_t glyphDef = glyphs[c];
    for(uint8_t index = 0; index < 8; index++) {
        bool state = (bool)(glyphDef & (1 << index));
        digitalWrite(segmentPins[index],(uint8_t) (state ? SEGMENT_ON : SEGMENT_OFF));
    }
}

void CL5642BH_33::setupPins() {
    pinMode(digit1, OUTPUT);
    pinMode(digit2, OUTPUT);
    pinMode(digit3, OUTPUT);
    pinMode(digit4, OUTPUT);
    pinMode(segmentA, OUTPUT);
    pinMode(segmentB, OUTPUT);
    pinMode(segmentC, OUTPUT);
    pinMode(segmentD, OUTPUT);
    pinMode(segmentE, OUTPUT);
    pinMode(segmentF, OUTPUT);
    pinMode(segmentG, OUTPUT);
    pinMode(digitalPoint, OUTPUT);
}