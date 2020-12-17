#include "sensors.h"

Sensors::Sensors() {
    address = 0;
    temperature = 0;
    humidity = 0;
    hic = 0;
    pm10 = 0;
    pm25 = 0;
    pm_concentration = 0;
}

Sensors::Sensors(uint8_t iaddress) {
    address = iaddress;
    temperature = 0;
    humidity = 0;
    hic = 0;
    pm10 = 0;
    pm25 = 0;
    pm_concentration = 0;
}


uint8_t Sensors::toI2C(void) {
    int i = 0;
    uint8_t bytes = 24;
    uint8_t data[24];

    // Exports temperature
    for (int j=0; j<4; j++) {
        data[i] = ((uint8_t*)&temperature)[i];
        i++;
    }
    // Exports humidity
    for (int j=0; j<4; j++) {
        data[i] = ((uint8_t*)&humidity)[j];
        i++;
    }
    // Exports hic
    for (int j=0; j<4; j++) {
        data[i] = ((uint8_t*)&hic)[j];
        i++;
    }
    // Exports pm10
    for (int j=0; j<4; j++) {
        data[i] = ((uint8_t*)&pm10)[j];
        i++;
    }
    // Exports pm25
    for (int j=0; j<4; j++) {
        data[i] = ((uint8_t*)&pm25)[j];
        i++;
    }
    // Exports pm_concentration
    for (int j=0; j<4; j++) {
        data[i] = ((uint8_t*)&pm_concentration)[j];
        i++;
    }

#ifdef __AVR_ATtiny85__
    uint8_t n = TinyWire.send(data, bytes);
#else
    uint8_t n = Wire.write(data, bytes);
#endif

    return n;
}


uint8_t Sensors::fromI2C(void) {
    int i = 0;
    uint8_t bytes = 24;
    uint8_t data[24];

#ifdef __AVR_ATtiny85__
    uint8_t n = TinyWire.requestFrom(address, bytes);
#else
    uint8_t n = Wire.requestFrom(address, bytes);
#endif

    if (n != bytes) {
        return 0;
    }

#ifdef __AVR_ATtiny85__
    //TinyWire.readBytes(data, bytes);
#else
    Wire.readBytes(data, bytes);
#endif

    // Imports temperature
    for (int j=0; j<4; j++) {
        ((uint8_t*)&temperature)[j] = data[i];
        i++;
    }
    // Imports temperature
    for (int j=0; j<4; j++) {
        ((uint8_t*)&humidity)[j] = data[i];
        i++;
    }
    // Imports hic
    for (int j=0; j<4; j++) {
        ((uint8_t*)&hic)[j] = data[i];
        i++;
    }
    // Imports pm10
    for (int j=0; j<4; j++) {
        ((uint8_t*)&pm10)[j] = data[i];
        i++;
    }
    // Imports pm25
    for (int j=0; j<4; j++) {
        ((uint8_t*)&pm25)[j] = data[i];
        i++;
    }
    // Imports pm_concentration
    for (int j=0; j<4; j++) {
        ((uint8_t*)&pm_concentration)[j] = data[i];
        i++;
    }
    return bytes;
}

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
