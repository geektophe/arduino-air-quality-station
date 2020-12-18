#include <stdio.h>
#include "station.h"

Station::Station(void) {
    dht = NULL;
    dht_last_update = 0;
    dsm501 = NULL;
    lcd = NULL;
    lcd_page = 0;
    sensors = NULL;
}


void Station::setSensors(sensors_t *psensors) {
    sensors = psensors;
}


void Station::setDHT(DHTNEW *pdht) {
    dht = pdht;
}


void Station::setDSM501(DSM501 *pdsm501) {
    dsm501 = pdsm501;
}


void Station::setLCD(LiquidCrystal_I2C *plcd) {
    lcd = plcd;
}


bool Station::readSensors(void) {
    bool update = false;

    if (dht && readTemperature()) {
        update = true;
    }
    if (dsm501 && readPM()) {
        update = true;
    }
    return update;
}


bool Station::readTemperature(void) {
    unsigned long now = millis();
    bool update = false;

    // millis() can cycle
    if (now < dht_last_update) {
        dht_last_update = 0;
    }

    if (now - dht_last_update > TEMPERATURE_SAMPLE_TIME * 1000) {
        Serial.println("Reading Temperature");
        // La lecture du capteur prend 250ms
        // Les valeurs lues peuvet etre vieilles de jusqu'a 2 secondes (le capteur est lent)

        int err = dht->read();
        float h = dht->getHumidity();
        float t = dht->getTemperature();

        //On verifie si la lecture a echoue, si oui on quitte la boucle pour recommencer.
        if (err != DHTLIB_OK) {
            Serial.print("Failed to read from DHT sensor! [err=");
            Serial.print(err);
            Serial.println("]");
        } else {
            Serial.println("Successfully read temperature");
            sensors->temperature = t;
            sensors->humidity = h;
            update = true;
        }
        dht_last_update = now;
    }
    return update;
}


bool Station::readPM(void) {
    bool update = false;

    if (dsm501->update()) {
        Serial.println("Reading PM");
        sensors->pm10 = dsm501->getParticleCount(0);
        sensors->pm25 = dsm501->getParticleCount(1);
        sensors->pm_concentration = dsm501->getConcentration();
        update = true;
    }
    return update;
}

/*
unsigned int calculateATMOIndex(void) {
    if () {

    }
}
*/


void Station::display(void) {
    displaySerial();
    if (lcd) {
        displayLCD();
    }
}


void Station::displaySerial(void) {
    Serial.print("Humidity: ");
    Serial.print(sensors->humidity);
    Serial.println(" %\t");
    Serial.print("Temperature: ");
    Serial.print(sensors->temperature);
    Serial.println(" *C\t");
    Serial.print("Heat index: ");
    Serial.print(sensors->hic);
    Serial.println(" *C");

    Serial.print("PM1.0 particle count: ");
    Serial.print(sensors->pm10);
    Serial.println(" parts/283mL");

    Serial.print("PM2.5 particle count: ");
    Serial.print(sensors->pm25);
    Serial.println(" parts/283mL");

    Serial.print("PM1.0 ~ PM2.5 concentration: ");
    Serial.print(sensors->pm_concentration);
    Serial.println(" ug/m3");
    Serial.println();
}


void Station::displayLCD(void) {
    unsigned long now = millis();

    // millis() can cycle
    if (now < lcd_last_update) {
        lcd_last_update = 0;
    }

    if (now - lcd_last_update > 5 * 1000) {
        lcd->clear();
        switch (lcd_page) {
            case 0: Station::displayLCD_page1(); break;
            case 1: Station::displayLCD_page2(); break;
            case 2: Station::displayLCD_page3(); break;
        }
        if (lcd_page < 2) {
            lcd_page++;
        } else {
            lcd_page = 0;
        }
        lcd_last_update = now;
    }
}


void Station::displayLCD_page1(void) {
    char buffer[17];
    lcd->setCursor(0, 0);
    snprintf(buffer, 17, "Temp%10.1f C", (double)(sensors->temperature));
    Serial.println(buffer);
    lcd->print(buffer);
    lcd->setCursor(0, 1);
    snprintf(buffer, 17, "Humidity%6.1f p", (double)(sensors->humidity));
    Serial.println(buffer);
    lcd->print(buffer);
}


void Station::displayLCD_page2(void) {
    char buffer[17];
    lcd->setCursor(0, 0);
    snprintf(buffer, 17, "PM 1.0%10.0f", (double)(sensors->pm10));
    Serial.println(buffer);
    lcd->print(buffer);
    lcd->setCursor(0, 1);
    snprintf(buffer, 17, "PM 2.5%10.0f", (double)(sensors->pm25));
    Serial.println(buffer);
    lcd->print(buffer);
}


void Station::displayLCD_page3(void) {
    char buffer[17];
    lcd->setCursor(0, 0);
    snprintf(buffer, 17, "C PM10~25%7.0f", (double)(sensors->pm_concentration));
    Serial.println(buffer);
    lcd->print(buffer);
    lcd->setCursor(0, 1);
    /*
    snprintf(buffer, 17, "IQA   :  %2.1f p", (double)humidity);
    lcd->print(buffer);
    */
}

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
