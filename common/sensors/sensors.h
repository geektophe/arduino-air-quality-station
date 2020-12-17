#ifndef _SENSORS_H
#include <stdint.h>

#ifdef __AVR_ATtiny85__
#include <TinyWire.h>
#else
#include <Wire.h>
#endif

class Sensors {
    public:
        // I2C address
        uint8_t address;
        // Temperature sensor
        float temperature;
        float humidity;
        float hic;
        // PM Sensor
        float pm10;
        float pm25;
        float pm_concentration;

        Sensors(void);
        Sensors(uint8_t);
        uint8_t toI2C(void);
        uint8_t fromI2C(void);
};

typedef Sensors sensors_t;

#define _SENSORS_H
#endif

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
