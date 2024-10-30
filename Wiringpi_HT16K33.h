/*
 * Wiringpi_HT16K33.h
 * Released under the MIT license
 * Copyright (c) 2024 MikataHara
 * 2024.10.26
 */

#include <wiringPiI2C.h>

#ifndef _WIRINGPI_HT16K33_H
#define _WIRINGPI_HT16K33_H

#define HT16K33_I2CADDR_DEFAULT 0x70    ///< I2C address

/*  Class for MCP9808 Temp Sensor */

class Wiringpi_HT16K33 {
public:
    Wiringpi_HT16K33(uint8_t val);

    void write(uint8_t val);
    void write8(uint8_t reg, uint8_t val);
    uint8_t read8(uint8_t reg);

    void allClear();
    void allGreen();
    void allRed();
    void allOrange();

    void DispNum(uint8_t n);
    void DisplayOutput(uint8_t* GndDot, uint8_t* RndDot);
    void RotateMatrix(uint8_t *Buf1, uint8_t *Buf2);

private:
    uint8_t _i2caddr;
};

#endif
