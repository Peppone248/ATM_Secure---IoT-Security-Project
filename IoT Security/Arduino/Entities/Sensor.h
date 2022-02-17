#include <time.h>

//SENSORS PIN
const int DHT11_PIN = 2;
const int RELAY_PIN = 3;
const int MOTION_PIN = 4;
const int LH_MAGNETIC_AO_PIN = A1;
const int BIG_SOUND_AO_PIN = A2;
const int PHOTO_RES_PIN = A3;

bool debugMode = false;

class Sensor
{
protected:
    int pin;

public:
    Sensor(int pin)
    {
        this->pin = pin;
        debugMode = false;
    };
    Sensor(){};
    virtual void measureValue(char *value);
};
