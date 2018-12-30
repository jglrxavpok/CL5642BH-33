//
// Created by jglrxavpok on 29/12/18.
//

#ifndef TESTINIT_CL5642BH_33_H
#define TESTINIT_CL5642BH_33_H
#include <stdint.h>

constexpr uint8_t DISPLAY_BRIGHTNESS = 500;

#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

int sign(long number);

class CL5642BH_33 {
public:
    CL5642BH_33(uint8_t digit1, uint8_t digit2, uint8_t digit3, uint8_t digit4,
                uint8_t segmentA, uint8_t segmentB, uint8_t segmentC, uint8_t segmentD, uint8_t segmentE, uint8_t segmentF, uint8_t segmentG,
                uint8_t digitalPoint);

    /**
     * Array representing all standard ASCII characters. A glyph is represented by a 7 bit (8 bits but 8th ignored) representing the state of each segment (from A to G).
     * Initialized in the constructor to the glyph table in 'glyphs.h'
     */
    uint8_t glyphs[128];

    /**
     * The 4 characters to draw.
     */
    char glyphBuffer[4];

    /**
     * Should Nth digital point be light up?
     * /!\ The first one is not accessible in order to make room for the colon on the CL5642BH-33
     */
    bool digitalPoints[4];

    /**
     * Should the colon be lit up?
     */
    bool lightUpColon = false;

    /**
     * This method is made to last at least 10ms (in ensure the display is correctly painted).
     * It simply calls 'paintAsync' and then waits
     */
    void paint();

    /**
     * This method will not last for 10ms but will immediately return if the last paint was less than 10ms ago
     */
    void paintAsync();

    /**
     * Call in your 'setup' function to setup the pins to OUTPUT (not required but less code to write)
     */
    void setupPins();

private:
    // PINS
    uint8_t digit1, digit2, digit3, digit4;
    uint8_t segmentA, segmentB, segmentC, segmentD, segmentE, segmentF, segmentG, digitalPoint;
    uint8_t digitPins[4];
    uint8_t segmentPins[7];

    void initArrays();
    void drawCharacter(char c);
    void clearCharacter();
};


#endif //TESTINIT_CL5642BH_33_H
