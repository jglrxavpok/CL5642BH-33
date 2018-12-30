//
// Created by jglrxavpok on 29/12/18.
//

#include <string.h>
#include "glyphs.h"

void initDefaultGlyphTable(uint8_t* glyphTable) {
#define NON_REPRESENTABLE 0b0000000
    memset(glyphTable, NON_REPRESENTABLE, 128);

    glyphTable['!'] = 0b0000010;
    glyphTable['"'] = 0b0100010;
    glyphTable['&'] = 0b1111101;
    glyphTable['\''] = 0b0000010;
    glyphTable['('] = 0b0111001;
    glyphTable[')'] = 0b0001111;
    glyphTable[','] = 0b0001100;
    glyphTable['-'] = 0b1000000;
    glyphTable['/'] = 0b1010010;
    glyphTable['0'] = 0b0111111;
    glyphTable['1'] = 0b0000110;
    glyphTable['2'] = 0b1011011;
    glyphTable['3'] = 0b1001111;
    glyphTable['4'] = 0b1100110;
    glyphTable['5'] = 0b1101101;
    glyphTable['6'] = 0b1111101;
    glyphTable['7'] = 0b0000111;
    glyphTable['8'] = 0b1111111;
    glyphTable['9'] = 0b1101111;
    glyphTable['='] = 0b1001000;
    glyphTable['?'] = 0b1010011;

    glyphTable['A'] = 0b1110111;
    glyphTable['B'] = 0b1111100;
    glyphTable['C'] = 0b1011000;
    glyphTable['D'] = 0b1011110;
    glyphTable['E'] = 0b1111001;
    glyphTable['F'] = 0b1110001;
    glyphTable['G'] = 0b1111101;
    glyphTable['H'] = 0b1110100;
    glyphTable['I'] = 0b0000110;
    glyphTable['J'] = 0b0001110;
    glyphTable['K'] = 0b1110100;
    glyphTable['L'] = 0b0111000;
    glyphTable['M'] = 0b0110111;
    glyphTable['N'] = 0b1010100;
    glyphTable['O'] = 0b1011100;
    glyphTable['P'] = 0b1110011;
    glyphTable['Q'] = 0b1100111;
    glyphTable['R'] = 0b1010000;
    glyphTable['S'] = glyphTable['5'];
    glyphTable['T'] = 0b1111000;
    glyphTable['U'] = 0b0011100;
    glyphTable['V'] = 0b0111110;
    glyphTable['W'] = glyphTable['V'];
    glyphTable['X'] = 0b1110110;
    glyphTable['Y'] = 0b1101110;
    glyphTable['Z'] = glyphTable['2'];

    glyphTable['['] = glyphTable['('];
    glyphTable[']'] = glyphTable[')'];
    glyphTable['{'] = glyphTable['('];
    glyphTable['}'] = glyphTable[')'];
    glyphTable['~'] = glyphTable['-'];
    glyphTable['\\'] = 0b1100100;
    glyphTable['_'] = 0b0001000;

    // lower case and upper case glyphs are the same
    memcpy(&glyphTable['a'], &glyphTable['A'], 26);
}