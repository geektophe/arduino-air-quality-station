#ifndef _STATION_H
#include <DSM501.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>


#define TEMPERATURE_SAMPLE_TIME 5

class Station {
    protected:
        // Temperature related variables
        DHT *dht;
        float temperature;
        float humidity;
        float hic;
        unsigned long dht_last_update;
        // Temperature related methods
        bool readTemperature(void);

        // PM related variables
        DSM501 *dsm501;
        float pm10;
        float pm25;
        float pm_concentration;
        // PM related methods
        bool readPM(void);
        unsigned int calculateATMOIndex(void);

        // LCD related variables
        LiquidCrystal_I2C *lcd;
        unsigned int lcd_page;
        unsigned long lcd_last_update;
        // LCD related methods
        void displaySerial(void);
        void displayLCD(void);
        void displayLCD_page1(void);
        void displayLCD_page2(void);
        void displayLCD_page3(void);

    public:
        Station();
        void setDHT(DHT*);
        void setDSM501(DSM501*);
        void setLCD(LiquidCrystal_I2C*);
        bool readSensors(void);
        void display(void);
} ;

typedef Station station_t;
#define _STATION_H
#endif
// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
