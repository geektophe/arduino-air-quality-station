#include "satellite.h"


Satellite::Satellite(void) {
    sensors = NULL;
    dht = NULL;
    dsm501 = NULL;
    sensors->pm10 = 0;
    dht_last_update = 0;
}


Satellite::Satellite(sensors_t *psensors) {
    sensors = psensors;
    dht = NULL;
    dsm501 = NULL;
    sensors->pm10 = 0;
    dht_last_update = 0;
}


void Satellite::setSensors(sensors_t *psensors) {
    sensors = psensors;
}


void Satellite::setDHT(DHT *pdht) {
    dht = pdht;
}


void Satellite::setDSM501(DSM501 *pdsm501) {
    dsm501 = pdsm501;
}


bool Satellite::readSensors(void) {
    bool update = false;

    if (dht && readTemperature()) {
        update = true;
    }
    if (dsm501 && readPM()) {
        update = true;
    }
    return update;
}


bool Satellite::readTemperature(void) {
    unsigned long now = millis();
    bool update = false;

    // millis() can cycle
    if (now < dht_last_update) {
        dht_last_update = 0;
    }

    if (now - dht_last_update > TEMPERATURE_SAMPLE_TIME * 1000) {
        // La lecture du capteur prend 250ms
        // Les valeurs lues peuvet etre vieilles de jusqu'a 2 secondes (le capteur est lent)
        double h = dht->readHumidity();
        double t = dht->readTemperature();

        //On verifie si la lecture a echoue, si oui on quitte la boucle pour recommencer.
        if (isnan(h) || isnan(t)) {
            return false;
        } else {
            sensors->hic = dht->computeHeatIndex(t, h, false);
            sensors->temperature = t;
            sensors->humidity = h;
            update = true;
        }
        dht_last_update = now;
    }
    return update;
}


bool Satellite::readPM(void) {
    bool update = false;

    if (dsm501->update()) {
        sensors->pm10 = dsm501->getParticleCount(0);
        sensors->pm25 = dsm501->getParticleCount(1);
        sensors->pm_concentration = dsm501->getConcentration();
        update = true;
    }
    return update;
}

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
