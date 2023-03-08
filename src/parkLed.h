#ifndef PARKLED_H
#define PARKLED_H

#include <stdio.h>
#include <pigpio.h>
#include <iostream>

using namespace std;

class parkLed
{
    public:
        parkLed(int sensor_pin, int led_pin);
        void draw();
    private:
        int sensor_pin;
        int led_pin;
};

#endif //PARKLED_H