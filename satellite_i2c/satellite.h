#ifndef _SATELLITE_H
#include <DSM501.h>
#include <DHT.h>
#include <sensors.h>


#define TEMPERATURE_SAMPLE_TIME 5

class Satellite {
    protected:
        // Sensors data
        sensors_t *sensors;

        // Temperature related variables
        DHT *dht;
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

    public:
        Satellite(void);
        Satellite(sensors_t*);
        void setSensors(sensors_t*);
        void setDHT(DHT*);
        void setDSM501(DSM501*);
        bool readSensors(void);
};

typedef Satellite satellite_t;

#define _SATELLITE_H
#endif

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
