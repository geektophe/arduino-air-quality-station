#include <stdio.h>
#include "station.h"

// DSM51 sensor
#include <DSM501.h>
#define DSM501_PM1_0    2
#define DSM501_PM2_5    3
#define SAMPLE_TIME     15 // seconds

DSM501 dsm501;

// DHT22 sensor
#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT22 // DHT 22 (AM2302)

DHT dht(DHTPIN, DHTTYPE); //déclaration du capteur

// LCD screen
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Station
station_t station;

// I2C scanner
#include <Wire.h>


void i2cscan(void) {
    byte error, address; //variable for error and I2C address
    int nDevices;

    Serial.println("Scanning I2C bus...");

    nDevices = 0;
    for (address = 1; address < 127; address++ ) {
      // The i2c_scanner uses the return value of
      // the Write.endTransmisstion to see if
      // a device did acknowledge to the address.
      Wire.beginTransmission(address);
      error = Wire.endTransmission();

      if (error == 0) {
          Serial.print("I2C device found at address 0x");
          if (address < 16)
              Serial.print("0");
          Serial.print(address, HEX);
          Serial.println("  !");
          nDevices++;
      } else if (error == 4) {
          Serial.print("Unknown error at address 0x");
          if (address < 16)
              Serial.print("0");
          Serial.println(address, HEX);
      }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");
}

void setup() {
    Serial.begin(9600);
    delay(1000);
    Serial.println("Initializing I2C");
    Wire.begin();
    Serial.println("Done initializing I2C");
    i2cscan();

    // Initialize LCD screen
    Serial.print("Initializing display");
    lcd.init();
    lcd.backlight();
    Serial.print("Done initializing display");

    lcd.setCursor(0, 0);
    lcd.print("Initializing...");

    // Initialize DSM501
    //           PM1.0 pin     PM2.5 pin     sampling duration in seconds
    dsm501.begin(DSM501_PM1_0, DSM501_PM2_5, SAMPLE_TIME);

    // Initialize DHT22
    dht.begin();

    // Wait 60s for sensors to warm up
    char buffer[3];
    Serial.println("Wait 60s for sensors to warm up");
    for (int i = 1; i <= 60; i++) {
        delay(1000); // 1s
        snprintf(buffer, 3, "%02d", i);
        Serial.print(buffer);
        Serial.println("s (wait 60s for DSM501 to warm up)");
    }

    // Sets station internal variables
    station.setDHT(&dht);
    station.setDSM501(&dsm501);
    station.setLCD(&lcd);

    Serial.println("Sensors are ready!");
}

void loop() {
    if (station.readSensors()) {
        station.display();
    }
    delay(1000);
}

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
