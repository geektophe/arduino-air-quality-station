#include <TinyWire.h>
#ifndef TWI_RX_BUFFER_SIZE
#define TWI_RX_BUFFER_SIZE ( 16 )
#endif

#define I2C_SLAVE_ADDRESS 0x13

#include "satellite.h"

/*
// DSM51 sensor
#include <DSM501.h>
#define DSM501_PM1_0    2
#define DSM501_PM2_5    3
#define SAMPLE_TIME     15 // seconds

DSM501 dsm501;
*/

// DHT22 sensor
#include <dhtnew.h>
#define DHTPIN PB1
#define DHTTYPE DHT22 // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE);

// Sensors data
#include <sensors.h>
uint8_t address = I2C_SLAVE_ADDRESS;
sensors_t sensors(address);

// Satellite
satellite_t satellite(&sensors);


void requestEvent() {
    sensors.toI2C();
}


void setup() {
    TinyWire.begin(I2C_SLAVE_ADDRESS);
    TinyWire.onRequest(requestEvent);

    /*
    // Initialize DSM501
    //           PM1.0 pin     PM2.5 pin     sampling duration in seconds
    dsm501.begin(DSM501_PM1_0, DSM501_PM2_5, SAMPLE_TIME);
    */
    sensors.temperature = 1.1;
    sensors.humidity = 2.2;
    sensors.hic = 3.3;
    sensors.pm10 = 4.4;
    sensors.pm25 = 5.5;
    sensors.pm_concentration = 6.6;
    return;

    // Initialize DHT22
    dht.begin();

    // Wait 60s for sensors to warm up
    for (int i = 1; i <= 60 && false; i++) {
        delay(1000); // 1s
    }

    // Sets satellite internal variables
    satellite.setSensors(&sensors);
    satellite.setDHT(&dht);
    //satellite.setDSM501(&dsm501);
}

void loop() {
    // satellite.readSensors();
}

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
