#ifndef SENSOR_H
#define SENSOR_H
#include "Sensor.h"
#endif
#include "Arduino.h"
#include <TinyGPS.h>

TinyGPS gps;
float LO1 = 41.095f;
float HI1 = 41.096f;
float LO2 = 16.862f;
float HI2 = 16.863f;

class GPS : Sensor
{
    public:
    
        GPS() : Sensor(){};

        void setup()
        {
            Serial2.begin(9600); // connect gps sensor
        }

        void measureValue(char *value)
        {
            float lat = 41.095491, lon = 16.862459; // create variable for latitude and longitude
            value[0] = '\0';
            if (debugMode)
            {
                lat = LO1 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (HI1 - LO1)));
                lon = LO2 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (HI2 - LO2)));
            }
            else
            {
                unsigned long age;

                smartdelay(1000);
                gps.satellites();
                gps.hdop();
                gps.f_get_position(&lat, &lon, &age);
            }
            char latitude[12];
            char longitude[12];
            dtostrf(lat, 11, 6, latitude);
            dtostrf(lon, 11, 6, longitude);
            int len = sprintf(value, "GPS:Lat:%s;Lon:%s", latitude, longitude);
            value[len] = '\0';
        }

        static void smartdelay(unsigned int ms)
        {
            unsigned long start = millis();
            do
            {
                while (Serial2.available())
                    gps.encode(Serial2.read());
            } while (millis() - start < ms);
        }
};