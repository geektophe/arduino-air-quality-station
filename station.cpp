#include <stdio.h>
#include "station.h"

Station::Station(void) {
    dht = NULL;
    dsm501 = NULL;
    lcd = NULL;
    lcd_page = 0;
    pm10 = 0;
    pm25 = 0;
    pm_concentration = 0;
    temperature = 0;
    humidity = 0;
    hic = 0;
    dht_last_update = 0;
}

void Station::setDHT(DHT *pdht) {
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
        double h = dht->readHumidity();
        double t = dht->readTemperature();

        //On verifie si la lecture a echoue, si oui on quitte la boucle pour recommencer.
        if (isnan(h) || isnan(t)) {
            Serial.println("Failed to read from DHT sensor!");
        } else {
            Serial.println("Successfully read temperature");
            hic = dht->computeHeatIndex(t, h, false);
            temperature = t;
            humidity = h;
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
        pm10 = dsm501->getParticleCount(0);
        pm25 = dsm501->getParticleCount(1);
        pm_concentration = dsm501->getConcentration();
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
    Serial.print(humidity);
    Serial.println(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C\t");
    Serial.print("Heat index: ");
    Serial.print(hic);
    Serial.println(" *C");

    Serial.print("PM1.0 particle count: ");
    Serial.print(pm10);
    Serial.println(" parts/283mL");

    Serial.print("PM2.5 particle count: ");
    Serial.print(pm25);
    Serial.println(" parts/283mL");

    Serial.print("PM1.0 ~ PM2.5 concentration: ");
    Serial.print(pm_concentration);
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
    snprintf(buffer, 17, "Temp%10.1f C", (double)temperature);
    lcd->print(buffer);
    lcd->setCursor(0, 1);
    snprintf(buffer, 17, "Humidity%6.1f p", (double)humidity);
    lcd->print(buffer);
}


void Station::displayLCD_page2(void) {
    char buffer[17];
    lcd->setCursor(0, 0);
    snprintf(buffer, 17, "PM 1.0%10.0f", (double)pm10);
    lcd->print(buffer);
    lcd->setCursor(0, 1);
    snprintf(buffer, 17, "PM 2.5%10.0f", (double)pm25);
    lcd->print(buffer);
}


void Station::displayLCD_page3(void) {
    char buffer[17];
    lcd->setCursor(0, 0);
    snprintf(buffer, 17, "C PM10~25%7.0f", (double)pm_concentration);
    lcd->print(buffer);
    lcd->setCursor(0, 1);
    /*
    snprintf(buffer, 17, "IQA   :  %2.1f p", (double)humidity);
    lcd->print(buffer);
    */
}

// vim: tabstop=8 expandtab shiftwidth=4 softtabstop=4
